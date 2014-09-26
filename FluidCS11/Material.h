
#include "WICTextureLoader.h"

class Material
{
public:

	ID3D11ShaderResourceView *srv;
	ID3D11SamplerState *sample;

	Material(ID3D11ShaderResourceView *srv, ID3D11SamplerState *sample);

};