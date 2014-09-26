#include "DXUT.h"
#include"Material.h"
#include"WICTextureLoader.h"


Material::Material(ID3D11ShaderResourceView *srv, ID3D11SamplerState *sample)
{
	D3D11_SAMPLER_DESC sample_desc;

	sample_desc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	sample_desc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	sample_desc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	sample_desc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	sample_desc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	sample_desc.MinLOD = 0;
	sample_desc.MaxLOD = D3D11_FLOAT32_MAX;

}