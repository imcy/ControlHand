//////////////////////////////////////////////////////////////////////
//
//	C3dsReader, CKnuckle 和 CRobotHand 类的数据结构的定义.
//
//////////////////////////////////////////////////////////////////////

#ifndef GLSTRUCTURES_H
#define GLSTRUCTURES_H

const long SizeofChunk = sizeof(unsigned short)+sizeof(long);

//PI的宏定义
#define M_PI        3.141592653589
#define M_2PI       6.283185307178

// 定义块的结构
typedef struct {
    unsigned short		id;
    long				len;
} Chunk3DS;

// 定义块的标识
const unsigned short	M3DMAGIC			= 0x4d4d;
const unsigned short	CMAGIC				= 0xc23d;
const unsigned short	M3D_VERSION			= 0x0002;
const unsigned short	MDATA				= 0x3d3d;
const unsigned short	MESH_VERSION		= 0x3d3e;
const unsigned short	MAT_ENTRY			= 0xafff;
const unsigned short	MASTER_SCALE		= 0x0100;
const unsigned short	NAMED_OBJECT		= 0x4000;
const unsigned short	MAT_NAME			= 0xa000;
const unsigned short	MAT_AMBIENT			= 0xa010;
const unsigned short	MAT_DIFFUSE			= 0xa020;
const unsigned short	MAT_SPECULAR		= 0xa030;
const unsigned short	MAT_SHININESS		= 0xa040;
const unsigned short	MAT_TRANSPARENCY	= 0xa050;
const unsigned short	MAT_SHADING			= 0xa100;
const unsigned short	N_TRI_OBJECT		= 0x4100;
const unsigned short	POINT_ARRAY			= 0x4110;
const unsigned short	FACE_ARRAY			= 0x4120;
const unsigned short	MSH_MAT_GROUP		= 0x4130;
const unsigned short	SMOOTH_GROUP		= 0x4150;
const unsigned short	MESH_MATRIX			= 0x4160;
const unsigned short	COLOR_24			= 0x0011;
const unsigned short	LIN_COLOR_24		= 0x0012;
const unsigned short	COLOR_F				= 0x0010;
const unsigned short	INT_PERCENTAGE		= 0x0030;
const unsigned short	FLOAT_PERCENTAGE	= 0x0031;
const unsigned short	N_DIRECT_LIGHT		= 0x4600;
const unsigned short	N_CAMERA			= 0x4700;
const unsigned short	KFDATA				= 0xb000;
const unsigned short	KFHDR				= 0xb00a;
const unsigned short	KFSEG				= 0xb008;
const unsigned short	OBJECT_NODE_TAG		= 0xb002;
const unsigned short	NODE_ID				= 0xb030;
const unsigned short	NODE_HDR			= 0xb010;
const unsigned short	PIVOT				= 0xb013;
const unsigned short	POS_TRACK_TAG		= 0xb020;
const unsigned short	ROT_TRACK_TAG		= 0xb021;
const unsigned short	SCL_TRACK_TAG		= 0xb022;

#define W_TENS  1
#define W_CONT  (1<<1)
#define W_BIAS  (1<<2)
#define W_EASETO  (1<<3)
#define W_EASEFROM  (1<<4)

// 材料的数据结构
struct tMaterial {
	float		ambientColor[3];
	float		diffuseColor[3];
	float		specularColor[3];
	float		emissiveColor[3];
	float		shininess;
	float		transparency;
};

// 定义材料符号表
const int MaxMaterialDictEntries = 256;

class MaterialDict {
private:
	char*			m_name[MaxMaterialDictEntries];
	long			m_count;
	tMaterial		m_material[MaxMaterialDictEntries];
public:
	void Clear(void) 
	{
		for (int i = 0; i < m_count; i++) {
			if (m_name[i] != NULL) {
				delete [] m_name[i];
			}
		}
		m_count = 0;
	}

	MaterialDict(void)
	{
		m_count = 0;
		for (int i = 0; i < MaxMaterialDictEntries; i++) {
			m_name[i] = NULL;
		}
	}

	~MaterialDict(void) 
	{
		Clear();	
	}

	tMaterial* Lookup(char* name) 
	{
		for (long i = 0; i < m_count; i++) {
			if (strcmp(name, m_name[i]) == 0) {
				return &m_material[i];
			}
		}
		return NULL;
	}

	void Add(char* name, tMaterial& material)
	{
		if (Lookup(name) == NULL) {
			m_name[m_count] = new char[strlen(name)+1];
			strcpy(m_name[m_count], name);
			m_material[m_count++] = material;
		}
	}

	tMaterial* operator[](int index)
	{
		if (index >= 0 && index < m_count) {
			return &m_material[index];
		}
		return NULL;
	}

};


struct tVector		//位置矢量
{
	float x,y,z;
	tVector(float xv=0, float yv=0, float zv=0)
	{
		x = xv;
		y = yv;
		z = zv;
	}
};

struct tVectorRGBA	//RGBA颜色
{
	float r,g,b,a;
};

struct tQuaternion	//四元数
{
	float x,y,z,a;
};

struct Key		//帧结构
{
	float tension;
	float continuity;
	float bias;
	float easeto;
	float easefrom;
	long  time;
};

struct Poskey		//Poskey
{
	float tension;
	float continuity;
	float bias;
	float easeto;
	float easefrom;
	long  time;
	float pos[3];
};

struct Rotkey		//Rotkey
{
	float tension;
	float continuity;
	float bias;
	float easeto;
	float easefrom;
	long  time;
	float angle;
	float axis[3];
};


#endif