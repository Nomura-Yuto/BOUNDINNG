
#include "main.h"
#include "texture.h"


struct VERTEX_3D
{
	Float3 Position;
	Float4 Color;
	Float2 TexCoord;
};


void DrawSprite(int texNo, float x, float y, float width, float height, float u, float v, float uw, float vh)
{
	VERTEX_3D vertex[4];

	float hw, hh;
	hw = width * 0.5f;
	hh = height * 0.5f;

	vertex[0].Position = MakeFloat3(x + hw, y - hh, 0.0f);
	vertex[1].Position = MakeFloat3(x - hw, y - hh, 0.0f);
	vertex[2].Position = MakeFloat3(x + hw, y + hh, 0.0f);
	vertex[3].Position = MakeFloat3(x - hw, y + hh, 0.0f);

	Float4 color = MakeFloat4( 1.0f, 1.0f, 1.0f, 1.0f );
	vertex[0].Color = color;
	vertex[1].Color = color;
	vertex[2].Color = color;
	vertex[3].Color = color;

	vertex[0].TexCoord = MakeFloat2(u + uw, v);
	vertex[1].TexCoord = MakeFloat2(u,      v);
	vertex[2].TexCoord = MakeFloat2(u + uw, v + vh);
	vertex[3].TexCoord = MakeFloat2(u,      v + vh);

	SetTexture(texNo);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VERTEX_3D), (GLvoid*)&vertex->Position);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(VERTEX_3D), (GLvoid*)&vertex->Color);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VERTEX_3D), (GLvoid*)&vertex->TexCoord);

	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}


void DrawSpriteLeftTop(int texNo, float x, float y, float width, float height, float u, float v, float uw, float vh)
{
	VERTEX_3D vertex[4];

	vertex[0].Position = MakeFloat3(x + width, y,          0.0f);
	vertex[1].Position = MakeFloat3(x,         y,          0.0f);
	vertex[2].Position = MakeFloat3(x + width, y + height, 0.0f);
	vertex[3].Position = MakeFloat3(x,         y + height, 0.0f);

	Float4 color = MakeFloat4( 1.0f, 1.0f, 1.0f, 1.0f );
	vertex[0].Color = color;
	vertex[1].Color = color;
	vertex[2].Color = color;
	vertex[3].Color = color;

	vertex[0].TexCoord = MakeFloat2(u + uw, v);
	vertex[1].TexCoord = MakeFloat2(u,      v);
	vertex[2].TexCoord = MakeFloat2(u + uw, v + vh);
	vertex[3].TexCoord = MakeFloat2(u,      v + vh);

	SetTexture(texNo);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VERTEX_3D), (GLvoid*)&vertex->Position);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(VERTEX_3D), (GLvoid*)&vertex->Color);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VERTEX_3D), (GLvoid*)&vertex->TexCoord);

	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}


void DrawSpriteColor(int texNo, float x, float y, float width, float height, float u, float v, float uw, float vh, float r, float g, float b, float a)
{
	VERTEX_3D vertex[4];

	float hw, hh;
	hw = width * 0.5f;
	hh = height * 0.5f;

	vertex[0].Position = MakeFloat3(x + hw, y - hh, 0.0f);
	vertex[1].Position = MakeFloat3(x - hw, y - hh, 0.0f);
	vertex[2].Position = MakeFloat3(x + hw, y + hh, 0.0f);
	vertex[3].Position = MakeFloat3(x - hw, y + hh, 0.0f);

	Float4 color = MakeFloat4(r, g, b, a);
	vertex[0].Color = color;
	vertex[1].Color = color;
	vertex[2].Color = color;
	vertex[3].Color = color;

	vertex[0].TexCoord = MakeFloat2(u + uw, v);
	vertex[1].TexCoord = MakeFloat2(u,      v);
	vertex[2].TexCoord = MakeFloat2(u + uw, v + vh);
	vertex[3].TexCoord = MakeFloat2(u,      v + vh);

	SetTexture(texNo);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VERTEX_3D), (GLvoid*)&vertex->Position);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(VERTEX_3D), (GLvoid*)&vertex->Color);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VERTEX_3D), (GLvoid*)&vertex->TexCoord);

	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}


void DrawSpriteColorRotate(int texNo, float x, float y, float width, float height, float u, float v, float uw, float vh, float r, float g, float b, float a, float rot)
{
	VERTEX_3D vertex[4];

	float hw, hh, c, s;
	hw = width * 0.5f;
	hh = height * 0.5f;
	c = cosf(rot);
	s = sinf(rot);

	vertex[0].Position.x = x + c * hw - s * -hh;
	vertex[0].Position.y = y + s * hw + c * -hh;
	vertex[0].Position.z = 0.0f;

	vertex[1].Position.x = x + c * -hw - s * -hh;
	vertex[1].Position.y = y + s * -hw + c * -hh;
	vertex[1].Position.z = 0.0f;

	vertex[2].Position.x = x + c * hw - s * hh;
	vertex[2].Position.y = y + s * hw + c * hh;
	vertex[2].Position.z = 0.0f;

	vertex[3].Position.x = x + c * -hw - s * hh;
	vertex[3].Position.y = y + s * -hw + c * hh;
	vertex[3].Position.z = 0.0f;

	Float4 color = MakeFloat4(r, g, b, a);
	vertex[0].Color = color;
	vertex[1].Color = color;
	vertex[2].Color = color;
	vertex[3].Color = color;

	vertex[0].TexCoord = MakeFloat2(u + uw, v);
	vertex[1].TexCoord = MakeFloat2(u,      v);
	vertex[2].TexCoord = MakeFloat2(u + uw, v + vh);
	vertex[3].TexCoord = MakeFloat2(u,      v + vh);

	SetTexture(texNo);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VERTEX_3D), (GLvoid*)&vertex->Position);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(VERTEX_3D), (GLvoid*)&vertex->Color);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VERTEX_3D), (GLvoid*)&vertex->TexCoord);

	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}


void DrawSpriteColorRotateAxis(int texNo, float x, float y, float width, float height, float cx, float cy, float u, float v, float uw, float vh, float r, float g, float b, float a, float rot)
{
	VERTEX_3D vertex[4];

	float hw, hh, c, s;
	hw = width * 0.5f;
	hh = height * 0.5f;
	c = cosf(rot);
	s = sinf(rot);

	vertex[0].Position.x = (-cx + hw) * c - (-cy - hh) * s;
	vertex[0].Position.y = (-cx + hw) * s + (-cy - hh) * c;
	vertex[0].Position.z = 0.0f;

	vertex[1].Position.x = (-cx - hw) * c - (-cy - hh) * s;
	vertex[1].Position.y = (-cx - hw) * s + (-cy - hh) * c;
	vertex[1].Position.z = 0.0f;

	vertex[2].Position.x = (-cx + hw) * c - (-cy + hh) * s;
	vertex[2].Position.y = (-cx + hw) * s + (-cy + hh) * c;
	vertex[2].Position.z = 0.0f;

	vertex[3].Position.x = (-cx - hw) * c - (-cy + hh) * s;
	vertex[3].Position.y = (-cx - hw) * s + (-cy + hh) * c;
	vertex[3].Position.z = 0.0f;

	vertex[0].Position.x += cx + x;
	vertex[0].Position.y += cy + y;

	vertex[1].Position.x += cx + x;
	vertex[1].Position.y += cy + y;

	vertex[2].Position.x += cx + x;
	vertex[2].Position.y += cy + y;

	vertex[3].Position.x += cx + x;
	vertex[3].Position.y += cy + y;

	Float4 color = MakeFloat4(r, g, b, a);
	vertex[0].Color = color;
	vertex[1].Color = color;
	vertex[2].Color = color;
	vertex[3].Color = color;

	vertex[0].TexCoord = MakeFloat2(u + uw, v);
	vertex[1].TexCoord = MakeFloat2(u,      v);
	vertex[2].TexCoord = MakeFloat2(u + uw, v + vh);
	vertex[3].TexCoord = MakeFloat2(u,      v + vh);

	SetTexture(texNo);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VERTEX_3D), (GLvoid*)&vertex->Position);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(VERTEX_3D), (GLvoid*)&vertex->Color);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VERTEX_3D), (GLvoid*)&vertex->TexCoord);

	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}


