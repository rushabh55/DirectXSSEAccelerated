 
// Coded by Jan Vlietinck, 27 Dec 2009, V 1.3
// http://users.skynet.be/fquake/

#include <windows.h>
#include <d3d11.h>
#include <d3dcompiler.h>
#include "resource.h"
#include "stdio.h"
#include "timer.h"
#include "math.h"

#include "Algebra.h"
#include "TrackBall.h"

TrackBall trackBall;
float zoom = 1.2;


bool vsync = false; // redraw synced with screen refresh

bool drawSphere = false;
bool macCormack = true;
bool smoky = true;

  // size of volume
#define DIMXYZ 200

int DimX = DIMXYZ;
int DimY = DIMXYZ;
int DimZ = DIMXYZ;


WCHAR message[256];
float timer=0;

Timer time;
int fps=0;
int sourcePattern = 0;
int clear = 0;
int viewOrientation = 0; // 0,1,2  for xy slice, yz sice, xz slice
int viewSlice = DIMXYZ/2; 


typedef struct
{   
  float dim[4];   // size of volume

  int width;  // size viewport
  int height;
  int viewSlice;  // slice of volume to render
  int viewOrientation; // 0,1,2  for xy slice, yz sice, xz slice

  float mouse[4];
  float dragDirection[4];

  float orientation[4*4]; // rotation matrix

  float zoom;
  int   smoky; // toggle between fire or smoky simulation

} Wave3DConstants;

typedef struct
{
  ID3D11ShaderResourceView*  srv;
  ID3D11UnorderedAccessView* uav;
} Resource;

Resource NULLres = { NULL, NULL };



int ROWS, COLS;
#define HCOLS (COLS/2)
#define HROWS (ROWS/2)

int mouseButtonState = 0;
int mousePosX=0;
int mousePosY=0;

// at drag start
int mousePosXPrev=0;
int mousePosYPrev=0;


bool drag = false;
int mousePosXDragStart=0;
int mousePosYDragStart=0;

int mousePosXDragEnd=0;
int mousePosYDragEnd=0;


int g_width, g_height; // size of window



#define SAFE_RELEASE(p)      { if(p) { (p)->Release(); (p)=NULL; } }




HINSTANCE                           g_hInst = NULL;
HWND                                g_hWnd = NULL;
D3D_DRIVER_TYPE                     g_driverType = D3D_DRIVER_TYPE_NULL;
ID3D11Device*                       g_pd3dDevice = NULL;
ID3D11DeviceContext*                g_pImmediateContext = NULL ;

IDXGISwapChain*                     g_pSwapChain = NULL;




ID3D11ComputeShader*        g_pCSDrawSphere;
ID3D11ComputeShader*        g_pCSAdvect3D;
ID3D11ComputeShader*        g_pCSAdvectBackward3D;
ID3D11ComputeShader*        g_pCSMacCormack3D;
ID3D11ComputeShader*        g_pCSDivergence3D;
ID3D11ComputeShader*        g_pCSJaccobi3D;
ID3D11ComputeShader*        g_pCSProject3D;

ID3D11ComputeShader*        g_pCSRender;
ID3D11ComputeShader*        g_pCSVectorToScalar;

ID3D11Buffer*		    				g_pcbWave3D;       // constant buffer


ID3D11SamplerState*         g_pSamplerStateLinear;

 // render output
Resource                 pRenderOutput; 

// Speed
ID3D11Texture3D*          pSpeedTex[3];
Resource pSpeed[3];

ID3D11Texture3D*          pSpeedSizeTex;
Resource pSpeedSize;

// Divergence
ID3D11Texture3D*          pDivergenceTex;
Resource pDivergence;

// Pressure
ID3D11Texture3D*          pPressureTex[2];
Resource pPressure[2];



// temp 2d slice for vector to scalar conversion
ID3D11Texture2D*           pSliceTex;
ID3D11UnorderedAccessView* pSliceUAV;
ID3D11ShaderResourceView*  pSliceSRV;


//--------------------------------------------------------------------------------------
// Forward declarations
//--------------------------------------------------------------------------------------
HRESULT InitWindow( HINSTANCE hInstance, int nCmdShow );
HRESULT InitDevice();
void CleanupDevice();
LRESULT CALLBACK    WndProc( HWND, UINT, WPARAM, LPARAM );
void Render();


//--------------------------------------------------------------------------------------
// Entry point to the program. Initializes everything and goes into a message processing 
// loop. Idle time is used to render the scene.
//--------------------------------------------------------------------------------------
//***********************************************************************************
int WINAPI wWinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow )
//***********************************************************************************
{

  COLS = (LONG)::GetSystemMetrics( SM_CXSCREEN );
  ROWS = (LONG)::GetSystemMetrics( SM_CYSCREEN );

  SetCursorPos(HCOLS, HROWS); // set mouse to middle screen


  if( FAILED( InitWindow( hInstance, nCmdShow ) ) )
      return 0;

  if( FAILED( InitDevice() ) )
  {
      CleanupDevice();
      return 0;
  }


  time.Start();

  // Main message loop
  MSG msg = {0};
  while( WM_QUIT != msg.message )
  {
      if( PeekMessage( &msg, NULL, 0, 0, PM_REMOVE ) )
      {
          TranslateMessage( &msg );
          DispatchMessage( &msg );
      }
      else
      {
          Render();
      }
  }

  CleanupDevice();

  return ( int )msg.wParam;
}




//--------------------------------------------------------------------------------------
// Register class and create window
//--------------------------------------------------------------------------------------
//***********************************************************************************
HRESULT InitWindow( HINSTANCE hInstance, int nCmdShow )
//***********************************************************************************
{
    // Register class
    WNDCLASSEX wcex;
    wcex.cbSize = sizeof( WNDCLASSEX );
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon( hInstance, ( LPCTSTR )IDI_MAIN_ICON );
    wcex.hCursor = LoadCursor( NULL, IDC_ARROW );
    wcex.hbrBackground = ( HBRUSH )( COLOR_WINDOW + 1 );
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = L"Wave3DWindowClass";
    wcex.hIconSm = LoadIcon( wcex.hInstance, ( LPCTSTR )IDI_MAIN_ICON );
    if( !RegisterClassEx( &wcex ) )
        return E_FAIL;

    // Create window
    // Create window
    g_hInst = hInstance;
    RECT rc = { COLS/2-3*ROWS/8, ROWS/2-3*ROWS/8, COLS/2 + 3*ROWS/8, ROWS/2+3*ROWS/8};
    AdjustWindowRect( &rc, WS_OVERLAPPEDWINDOW, FALSE );

    g_hWnd = CreateWindow( L"Wave3DWindowClass", L"", WS_OVERLAPPEDWINDOW, rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top, NULL, NULL, hInstance, NULL );

    if( !g_hWnd )
        return E_FAIL;

    ShowWindow( g_hWnd, nCmdShow );

    return S_OK;
}



//***********************************************************************************
void Resize()
//***********************************************************************************
{
  
  if ( g_pd3dDevice == NULL)
    return;

  HRESULT hr = S_OK;

  RECT rc;
  GetClientRect( g_hWnd, &rc );
  UINT width = rc.right - rc.left;
  UINT height = rc.bottom - rc.top;

  g_height = height;
  g_width  = width;

  


  // release references to back buffer before resize, else fails
  SAFE_RELEASE(pRenderOutput.uav);


  DXGI_SWAP_CHAIN_DESC sd;
  g_pSwapChain->GetDesc(&sd);
  hr = g_pSwapChain->ResizeBuffers(sd.BufferCount, width, height, sd.BufferDesc.Format, 0);

  ID3D11Texture2D* pTexture;
  hr = g_pSwapChain->GetBuffer( 0, __uuidof( ID3D11Texture2D ), ( LPVOID* )&pTexture );


  // create shader unordered access view on back buffer for compute shader to write into texture  
  hr = g_pd3dDevice->CreateUnorderedAccessView( pTexture, NULL, &pRenderOutput.uav );

  pTexture->Release();



  // Setup the viewport
  D3D11_VIEWPORT vp;
  vp.Width = width;
  vp.Height = height;
  vp.MinDepth = 0.0f;
  vp.MaxDepth = 1.0f;
  vp.TopLeftX = 0;
  vp.TopLeftY = 0;
  g_pImmediateContext->RSSetViewports( 1, &vp );

}

//***********************************************************************************
void CreateVolumes()
//***********************************************************************************
{

  unsigned short  *volume = new  unsigned short[DimX*DimY*DimZ*4];

  memset(volume, 0, DimX*DimY*DimZ*2*4);

  D3D11_TEXTURE3D_DESC desc;
  desc.Width              = DimX;
  desc.Height             = DimY;
  desc.Depth              = DimZ;
  desc.MipLevels          = 1; 
  desc.Format             = DXGI_FORMAT_R16G16B16A16_FLOAT;
  desc.Usage              = D3D11_USAGE_DEFAULT    ;    // D3D11_USAGE_STAGING  for mapping + copy cpu to gpu
  desc.BindFlags          = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_UNORDERED_ACCESS ;
  desc.CPUAccessFlags     = 0;  // D3D11_CPU_ACCESS_WRITE  or D3D11_CPU_ACCESS_READ for mapping
  desc.MiscFlags          = 0;


  D3D11_SUBRESOURCE_DATA data;
  data.pSysMem = volume;
  data.SysMemPitch = DimX*4*2;
  data.SysMemSlicePitch = DimX*DimY*4*2;


  for (int i =0; i<3; i++)
  {
    g_pd3dDevice->CreateTexture3D(&desc, &data, &pSpeedTex[i]);
    g_pd3dDevice->CreateUnorderedAccessView( pSpeedTex[i], NULL, &pSpeed[i].uav);
    g_pd3dDevice->CreateShaderResourceView(  pSpeedTex[i], NULL, &pSpeed[i].srv);
  }


  
  // half format  s eeeee  mmmmmmmmmm
  //  s : sign bit of float
  //  eeeee : exponent range [-15 15], stored as unsigned exponent + 15
  //  mmmmmmmmm : mantisse
  

  // Pressure
  desc.Format             = DXGI_FORMAT_R16G16B16A16_FLOAT; 
  desc.Width              = DimX/4;

  data.SysMemPitch = DimX*2;
  data.SysMemSlicePitch = DimX*DimY*2;

  for (int i =0; i<2; i++)
  {
    // create grow volume
    g_pd3dDevice->CreateTexture3D(&desc, &data, &pPressureTex[i]);
    g_pd3dDevice->CreateUnorderedAccessView( pPressureTex[i], NULL, &pPressure[i].uav);
    g_pd3dDevice->CreateShaderResourceView(  pPressureTex[i], NULL, &pPressure[i].srv);
  }

  // Divergence
  g_pd3dDevice->CreateTexture3D(&desc, &data, &pDivergenceTex);
  g_pd3dDevice->CreateUnorderedAccessView( pDivergenceTex, NULL, &pDivergence.uav);
  g_pd3dDevice->CreateShaderResourceView(  pDivergenceTex, NULL, &pDivergence.srv);


  // speed size (length velocity vector)
  desc.Format             = DXGI_FORMAT_R16_FLOAT; 
  desc.Width              = DimX;
  g_pd3dDevice->CreateTexture3D(&desc, NULL, &pSpeedSizeTex);
  g_pd3dDevice->CreateUnorderedAccessView( pSpeedSizeTex, NULL, &pSpeedSize.uav);
  g_pd3dDevice->CreateShaderResourceView(  pSpeedSizeTex, NULL, &pSpeedSize.srv);


  delete [] volume;


  // temp 2d slice in for to vector to scalar conversion

  D3D11_TEXTURE2D_DESC desc2;
  desc2.Width              = DimX;
  desc2.Height             = DimY;
  desc2.MipLevels          = 1; 
  desc2.ArraySize          = 1;
  desc2.SampleDesc.Count   = 1;
  desc2.SampleDesc.Quality = 0;
  desc2.Format             = DXGI_FORMAT_R16_FLOAT;
  desc2.Usage              = D3D11_USAGE_DEFAULT    ;    // D3D11_USAGE_STAGING  for mapping + copy cpu to gpu
  desc2.BindFlags          = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_UNORDERED_ACCESS ;
  desc2.CPUAccessFlags     = 0;  // D3D11_CPU_ACCESS_WRITE  or D3D11_CPU_ACCESS_READ for mapping
  desc2.MiscFlags          = 0;
  g_pd3dDevice->CreateTexture2D(&desc2, NULL, &pSliceTex);
  g_pd3dDevice->CreateUnorderedAccessView( pSliceTex, NULL, &pSliceUAV);
  g_pd3dDevice->CreateShaderResourceView(  pSliceTex, NULL, &pSliceSRV);
}


//--------------------------------------------------------------------------------------
// Create Direct3D device and swap chain
//--------------------------------------------------------------------------------------
//***********************************************************************************
HRESULT InitDevice()
//***********************************************************************************
{
    HRESULT hr = S_OK;

    RECT rc;
    GetClientRect( g_hWnd, &rc );
    UINT width = rc.right - rc.left;
    UINT height = rc.bottom - rc.top;

    UINT createDeviceFlags = 0;
#ifdef _DEBUG
    createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

    D3D_DRIVER_TYPE driverTypes[] =
    {
#ifdef WARP
      D3D_DRIVER_TYPE_REFERENCE,
#else
      D3D_DRIVER_TYPE_HARDWARE,        
#endif
    };
    UINT numDriverTypes = sizeof( driverTypes ) / sizeof( driverTypes[0] );

    DXGI_SWAP_CHAIN_DESC sd;
    ZeroMemory( &sd, sizeof( sd ) );
    sd.BufferCount = 1;
    sd.BufferDesc.Width = width;
    sd.BufferDesc.Height = height;
    sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    sd.BufferDesc.RefreshRate.Numerator = 60;
    sd.BufferDesc.RefreshRate.Denominator = 1;
    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT | DXGI_USAGE_UNORDERED_ACCESS | DXGI_USAGE_SHADER_INPUT;
    sd.OutputWindow = g_hWnd;
    sd.SampleDesc.Count = 1;
    sd.SampleDesc.Quality = 0;
    sd.Windowed = TRUE;
    //sd.Windowed = FALSE;
    //sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

    D3D_FEATURE_LEVEL FeatureLevels =   D3D_FEATURE_LEVEL_11_0;

    for( UINT driverTypeIndex = 0; driverTypeIndex < numDriverTypes; driverTypeIndex++ )
    {
        g_driverType = driverTypes[driverTypeIndex];
        hr = D3D11CreateDeviceAndSwapChain( NULL, g_driverType, NULL, createDeviceFlags, &FeatureLevels,1,
                                            D3D11_SDK_VERSION, &sd, &g_pSwapChain, &g_pd3dDevice, NULL, &g_pImmediateContext );
        if( SUCCEEDED( hr ) )
            break;
    }
    if( FAILED( hr ) )
        return hr;


    // Create constant buffer
    D3D11_BUFFER_DESC Desc;
    Desc.Usage = D3D11_USAGE_DYNAMIC;
    Desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    Desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    Desc.MiscFlags = 0;
    Desc.ByteWidth = ((sizeof( Wave3DConstants ) + 15)/16)*16; // must be multiple of 16 bytes
    g_pd3dDevice->CreateBuffer( &Desc, NULL, &g_pcbWave3D);
 



    // Create compute shader
    DWORD dwShaderFlags = 0;
    #if defined( DEBUG ) || defined( _DEBUG )
      dwShaderFlags |= D3D10_SHADER_DEBUG;
    #endif


    ID3D10Blob* pPSBuf = NULL;
    {
		
      hr = D3DCompileFromFile( L"fluid3D.hlsl", NULL, NULL, "CS_Advect3D", "cs_5_0", dwShaderFlags, NULL, NULL, &pPSBuf);
	  g_pCSAdvect3D = NULL;
      hr = g_pd3dDevice->CreateComputeShader( ( DWORD* )pPSBuf->GetBufferPointer(), pPSBuf->GetBufferSize(), NULL, &g_pCSAdvect3D );
      pPSBuf->Release();


      hr = D3DCompileFromFile( L"fluid3D.hlsl", NULL, NULL, "CS_AdvectBackward3D", "cs_5_0", dwShaderFlags, NULL, NULL, &pPSBuf);
      hr = g_pd3dDevice->CreateComputeShader( ( DWORD* )pPSBuf->GetBufferPointer(), pPSBuf->GetBufferSize(), NULL, &g_pCSAdvectBackward3D );
      pPSBuf->Release();


      hr = D3DCompileFromFile( L"fluid3D.hlsl", NULL, NULL, "CS_AdvectMacCormack3D", "cs_5_0", dwShaderFlags, NULL, NULL, &pPSBuf);
      hr = g_pd3dDevice->CreateComputeShader( ( DWORD* )pPSBuf->GetBufferPointer(), pPSBuf->GetBufferSize(), NULL, &g_pCSMacCormack3D );
      pPSBuf->Release();

      hr = D3DCompileFromFile( L"fluid3D.hlsl", NULL, NULL, "CS_Divergence3D", "cs_5_0", dwShaderFlags, NULL, NULL, &pPSBuf);
      hr = g_pd3dDevice->CreateComputeShader( ( DWORD* )pPSBuf->GetBufferPointer(), pPSBuf->GetBufferSize(), NULL, &g_pCSDivergence3D );
      pPSBuf->Release();
      hr = D3DCompileFromFile( L"fluid3D.hlsl", NULL, NULL, "CS_Jaccobi3D", "cs_5_0", dwShaderFlags, NULL, NULL, &pPSBuf);
      hr = g_pd3dDevice->CreateComputeShader( ( DWORD* )pPSBuf->GetBufferPointer(), pPSBuf->GetBufferSize(), NULL, &g_pCSJaccobi3D );
      pPSBuf->Release();
      hr = D3DCompileFromFile( L"fluid3D.hlsl", NULL, NULL, "CS_Project3D", "cs_5_0", dwShaderFlags, NULL, NULL, &pPSBuf );
      hr = g_pd3dDevice->CreateComputeShader( ( DWORD* )pPSBuf->GetBufferPointer(), pPSBuf->GetBufferSize(), NULL, &g_pCSProject3D );
      pPSBuf->Release();

      hr = D3DCompileFromFile( L"fluid3D.hlsl", NULL, NULL, "CS_DrawSphere", "cs_5_0", dwShaderFlags, NULL, NULL, &pPSBuf);
      hr = g_pd3dDevice->CreateComputeShader( ( DWORD* )pPSBuf->GetBufferPointer(), pPSBuf->GetBufferSize(), NULL, &g_pCSDrawSphere );
      pPSBuf->Release();
      hr = D3DCompileFromFile( L"fluid3D.hlsl", NULL, NULL, "CS_Render", "cs_5_0", dwShaderFlags, NULL, NULL, &pPSBuf);
      hr = g_pd3dDevice->CreateComputeShader( ( DWORD* )pPSBuf->GetBufferPointer(), pPSBuf->GetBufferSize(), NULL, &g_pCSRender);
      pPSBuf->Release();
    }


    CreateVolumes();


    // Create sampler state 
    D3D11_SAMPLER_DESC SSDesc;
    ZeroMemory( &SSDesc, sizeof( D3D11_SAMPLER_DESC ) );
    SSDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR ;
    SSDesc.AddressU = D3D11_TEXTURE_ADDRESS_BORDER ;   // zero speed at border
    SSDesc.AddressV = D3D11_TEXTURE_ADDRESS_BORDER ;
    SSDesc.AddressW = D3D11_TEXTURE_ADDRESS_BORDER ;
    SSDesc.BorderColor[0] = 0;
    SSDesc.BorderColor[1] = 0;
    SSDesc.BorderColor[2] = 0;
    SSDesc.BorderColor[3] = 0;
    SSDesc.MipLODBias = 0;
    SSDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
    SSDesc.MaxAnisotropy = 16;
    SSDesc.MinLOD = 0;
    SSDesc.MaxLOD = D3D11_FLOAT32_MAX;
    g_pd3dDevice->CreateSamplerState( &SSDesc, &g_pSamplerStateLinear );

    // set CS sampler
    g_pImmediateContext->CSSetSamplers(0,1, &g_pSamplerStateLinear);



    Resize();


    return S_OK;
}



//--------------------------------------------------------------------------------------
// Clean up the objects we've created
//--------------------------------------------------------------------------------------
//***********************************************************************************
void CleanupDevice()
//***********************************************************************************
{
    
    SAFE_RELEASE(pSliceUAV);
    SAFE_RELEASE(pSliceSRV);
    SAFE_RELEASE(pSliceTex);

    // release shaders
    SAFE_RELEASE(g_pCSDrawSphere);
    SAFE_RELEASE(g_pCSAdvect3D);
    SAFE_RELEASE(g_pCSRender);
    SAFE_RELEASE(g_pCSVectorToScalar);


    // release buffers
    SAFE_RELEASE( g_pcbWave3D );
    SAFE_RELEASE(pRenderOutput.uav);

    // release samplers
    SAFE_RELEASE(g_pSamplerStateLinear);


    if( g_pImmediateContext ) g_pImmediateContext->ClearState();

    if( g_pSwapChain )
    {
      g_pSwapChain->SetFullscreenState(false, NULL); // switch back to full screen else not working ok
      g_pSwapChain->Release();
    }

    if( g_pImmediateContext ) g_pImmediateContext->Release();
    if( g_pd3dDevice ) g_pd3dDevice->Release();
}





//--------------------------------------------------------------------------------------
// Called every time the application receives a message
//--------------------------------------------------------------------------------------
//***********************************************************************************
LRESULT CALLBACK WndProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam )
//***********************************************************************************
{
    PAINTSTRUCT ps;
    HDC hdc;
    
    static int viewSlicePrev;
    static bool rbdown = false;


  // Consolidate the mouse button messages and pass them to the right volume renderer
  if( msg == WM_LBUTTONDOWN ||
      msg == WM_LBUTTONUP ||
      msg == WM_LBUTTONDBLCLK ||
      msg == WM_MBUTTONDOWN ||
      msg == WM_MBUTTONUP ||
      msg == WM_MBUTTONDBLCLK ||
      msg == WM_RBUTTONDOWN ||
      msg == WM_RBUTTONUP ||
      msg == WM_RBUTTONDBLCLK ||
      msg == WM_MOUSEMOVE ||
      msg == WM_MOUSEWHEEL 
      )
  {

      mousePosXPrev = mousePosX;
      mousePosYPrev = mousePosY;

      mousePosX = (short)LOWORD(lParam);
      mousePosY = (short)HIWORD(lParam);

      int xPos = (short)LOWORD(lParam);
      int yPos = (short)HIWORD(lParam);
/*
      if (msg == WM_RBUTTONDOWN)
      {
        rbdown = true;
        viewSlicePrev = viewSlice;
        mousePosXDragStart  = mousePosX;
        mousePosYDragStart = mousePosY;
      }
      if (msg == WM_RBUTTONUP)
        rbdown = false;      

      if (rbdown)
          viewSlice = viewSlicePrev + (DimZ*(mousePosYDragStart-mousePosY))/g_height;
*/

      if (msg == WM_LBUTTONDOWN)
      {

        
        drag = true;
        drawSphere = true;
      }
      if (msg == WM_LBUTTONUP)
      {
        drag = false;
        drawSphere = false;
      }

      if (drag)
      {
        //mousePosXDragEnd = mousePosX;
        //mousePosYDragEnd = mousePosY;
      }



      int nMouseWheelDelta = 0;
      if( msg == WM_MOUSEWHEEL ) 
      {
        nMouseWheelDelta = (short) HIWORD(wParam);
        if (nMouseWheelDelta < 0)
          zoom = zoom * 1.1;
        else
          zoom = zoom / 1.1;
      }
  
      if (msg == WM_RBUTTONDOWN && !rbdown)
      {
          trackBall.DragStart(xPos, yPos, g_width, g_height);
          rbdown = true;
      }

      if (msg == WM_MOUSEMOVE && rbdown)
      {
        trackBall.DragMove(xPos, yPos, g_width, g_height);
      }

      if (msg == WM_RBUTTONUP)
      {
        trackBall.DragEnd();
        rbdown = false;
      }

  }





    else switch( msg)
    {
        case WM_PAINT:
            hdc = BeginPaint( hWnd, &ps );
            EndPaint( hWnd, &ps );
            break;

        case WM_CREATE:
        break;

        case WM_KEYDOWN:
		    {
          if( 'V' == (int)wParam || 'v' == (int)wParam)
          {
            vsync = !vsync;
          }


          if( 'C' == (int)wParam || 'c' == (int)wParam)
            clear =2;


			    switch( wParam )
			    {
            case VK_RETURN:
              viewOrientation = (viewOrientation+1)%3; // 0,1,2  for xy slice, yz sice, xz slice
            break;
				    case VK_ESCAPE:
              SendMessage( hWnd, WM_CLOSE, 0, 0 );
				    break;
            case VK_SPACE:
              //macCormack = !macCormack;
              smoky = !smoky;
            break;
          } 
          break;
        }


        case WM_KEYUP:
		    {
 			    if ( wParam == VK_SHIFT);
          break;
        }

        case WM_CLOSE:
          {
            DestroyWindow( hWnd );
            UnregisterClass( L"Wave3DWindowClass", NULL );
            return 0;
        }


        case WM_DESTROY:
            PostQuitMessage( 0 );
            break;



        case WM_SIZE:          
          if ( wParam != SIZE_MINIMIZED )
            Resize();
        break;


        default:
            return DefWindowProc( hWnd, msg, wParam, lParam );
    }

    return 0;
}


  //*************************************************************************
void SetConstantBuffer()
//*************************************************************************
{

// Fill constant buffer
  D3D11_MAPPED_SUBRESOURCE msr;
  g_pImmediateContext->Map(g_pcbWave3D, 0, D3D11_MAP_WRITE_DISCARD, 0,  &msr);
    Wave3DConstants mc;

    mc.dim[0] = DimX;
    mc.dim[1] = DimY;
    mc.dim[2] = DimZ;

    mc.width  = g_width;
    mc.height = g_height;

    mc.viewSlice = viewSlice;
    mc.viewOrientation = viewOrientation;


    mc.mouse[0] = (float)mousePosX; //  *DimX / g_width;
    mc.mouse[1] = (float)mousePosY; // * DimY / g_height;
    mc.mouse[2] = viewSlice;
    mc.mouse[3] = 3 ; // radius in voxels;


    // drag vector for speed impuls
    if (drag)
    {
      mc.dragDirection[0] = (float)(mousePosX - mousePosXPrev)*DimX / g_width;
      mc.dragDirection[1] = (float)(mousePosY - mousePosYPrev)*DimY / g_height;
    }
    else
    {
      mc.dragDirection[0] = 0;
      mc.dragDirection[1] = 0;
    }
    mc.dragDirection[2] = 0;

    for (int j=0; j<3; j++)
    for (int i=0; i<3; i++)
      mc.orientation[i + 4*j] = trackBall.GetRotationMatrix()(j,i);
    mc.zoom = zoom;
    mc.smoky = smoky;


    *(Wave3DConstants *)msr.pData = mc;
  g_pImmediateContext->Unmap(g_pcbWave3D,0);


  // set CS constant buffer
  ID3D11Buffer* ppCB[1] = { g_pcbWave3D };
  g_pImmediateContext->CSSetConstantBuffers( 0, 1, ppCB );
}

//*************************************************************************
void Swap( Resource &res0, Resource &res1)
//*************************************************************************
{
  Resource res;

  res = res0; res0 = res1; res1= res;
}


//*************************************************************************
void Unbind()
//*************************************************************************
{
    ID3D11ShaderResourceView* aSRiews[] = { NULL, NULL };
    g_pImmediateContext->CSSetShaderResources( 0, 2, aSRiews);

    ID3D11UnorderedAccessView* aUAViews[] = { NULL, NULL };
    g_pImmediateContext->CSSetUnorderedAccessViews( 0, 2, aUAViews, (UINT*)(&aUAViews) );
}

//*************************************************************************
  void RunShader(ID3D11ComputeShader *shader, Resource in0, Resource in1, Resource out0, Resource out1, int dx, int dy, int dz)
  //*************************************************************************
  {
    // Set volumes as textures for cached read
    ID3D11ShaderResourceView* aSRiews[] = { in0.srv, in1.srv };
    g_pImmediateContext->CSSetShaderResources( 0, 2, aSRiews);

    // Set unordered access views for writees
    ID3D11UnorderedAccessView* aUAViews[] = { out0.uav, out1.uav };
    g_pImmediateContext->CSSetUnorderedAccessViews( 0, 2, aUAViews, (UINT*)(&aUAViews) );

   // Set compute shader
    g_pImmediateContext->CSSetShader( shader,  NULL, 0 );

    // Run compute shader
    g_pImmediateContext->Dispatch( dx, dy, dz);

    Unbind();
  }

//*************************************************************************
  void RunShaders()
//*************************************************************************
 {
  // advect
  RunShader(g_pCSAdvect3D, pSpeed[0], NULLres, pSpeed[1], NULLres, (DimX+15)/16 , DimY/4, DimZ/4 );

  if (macCormack)
  {
    // backward advect and pre correct
    RunShader(g_pCSAdvectBackward3D, pSpeed[0], pSpeed[1], pSpeed[2], NULLres, (DimX+15)/16 , DimY/4, DimZ/4 );

    //  second order correction
    RunShader(g_pCSMacCormack3D, pSpeed[0], pSpeed[2], pSpeed[1], NULLres, (DimX+15)/16 , DimY/4, DimZ/4 );
  }

  // draw source
  RunShader(g_pCSDrawSphere, pSpeed[1], NULLres, pSpeed[0], NULLres, (DimX+15)/16 , DimY/4, DimZ/4 );
  

	// calc speed divergence
	RunShader(g_pCSDivergence3D, pSpeed[0], NULLres, pDivergence, NULLres, (DimX+63)/64 , DimY/4, DimZ/4 );

	// jaccobi
	for (int i=0; i<10; i++)
	{
	  RunShader(g_pCSJaccobi3D, pDivergence, pPressure[1], pPressure[0], NULLres, (DimX+63)/64 , DimY/4, DimZ/4 );
	  RunShader(g_pCSJaccobi3D, pDivergence, pPressure[0], pPressure[1], NULLres, (DimX+63)/64 , DimY/4, DimZ/4 );
	}

	// project
	RunShader(g_pCSProject3D, pSpeed[0], pPressure[1], pSpeed[1], pSpeedSize, (DimX+63)/64 , DimY/4, DimZ/4 );


  // render output
  RunShader(g_pCSRender, pSpeedSize, pPressure[1] , pRenderOutput, NULLres, (g_width+15)/16, (g_height+15)/16, 1 );


  Swap(pSpeed[0], pSpeed[1] );

}




//*************************************************************************
void Render()
//*************************************************************************
{

  SetConstantBuffer();

  RunShaders();

  // Present our back buffer to our front buffer
  g_pSwapChain->Present( vsync ? 1 : 0, 0 );


  float t;
  if ( (t=time.Elapsed()/1000) - timer > 1) // every second
  {  float td = t - timer; // real time interval a bit more than a second
    timer = t;
    //swprintf(message,L"Fluid3D V1.0      FPS %.2f     Slice %d", (float)fps/td, viewSlice);
    if (smoky)
      swprintf(message,L"Fluid3D MacCormack Smoky V1.3      FPS %.2f", (float)fps/td);
    else
      swprintf(message,L"Fluid3D MacCormack Fire  V1.3      FPS %.2f", (float)fps/td);
    SetWindowText(g_hWnd, message);
    fps=0;
  }
  fps++;

}






