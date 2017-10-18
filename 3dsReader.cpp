// 3dsReader.cpp: implementation of the C3dsReader class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "3DSLoader.h"
#include "3dsReader.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

C3dsReader::C3dsReader()
{

}

C3dsReader::~C3dsReader()
{

}

// 将块的内容读入块结构中
int C3dsReader::Read3DSChunk(FILE* fp, Chunk3DS& chunk)
{
	if (!ReadUShort(fp, chunk.id)) return FALSE;
	if (!ReadLong(fp, chunk.len)) return FALSE;
	return TRUE;
}

// 读入字符串，如果字符串的长度大于缓冲区，则截去多余的部分
int C3dsReader::Read3DSString(FILE* fp, char* name, int len /*= 256*/)
{
	int c;
	int i;
	for ( i=0; (c = fgetc(fp)) != EOF && c != '\0'; i++) {
		if (i < len) {
			name[i] = c;
		}
	}
	if (i < len) {
		name[i] = '\0';
	} else {
		name[len-1] = '\0';
	}

	return (c != EOF);
}

// 读入子块
int C3dsReader::ReadPercentage(FILE* fp, float& value)
{
	Chunk3DS	chunk;
	long		chunkStart = ftell(fp);

	if (!Read3DSChunk(fp, chunk)) return FALSE;
	
	if (chunk.id == INT_PERCENTAGE) 
	{
		short	svalue;
		if (!ReadShort(fp, svalue)) return FALSE;
		value = (float) svalue/ (float) 100.0;
		return TRUE;
	} else if (chunk.id == FLOAT_PERCENTAGE) 
	{
		if (!ReadFloat(fp, value)) return FALSE;
		return TRUE;
	} 

	fseek(fp, chunkStart + chunk.len, SEEK_SET);
	return FALSE;
}

// 读入颜色定义
int C3dsReader::ReadColor(FILE* fp, float& red, float& green, float& blue)
{
	Chunk3DS		chunk;
	long			chunkStart = ftell(fp);
	unsigned char	tmp;

	if (!Read3DSChunk(fp, chunk)) return FALSE;
	switch (chunk.id) 
	{
	case COLOR_F:
		if (!ReadFloat(fp, red)) return FALSE;
		if (!ReadFloat(fp, green)) return FALSE;
		if (!ReadFloat(fp, blue)) return FALSE;
		break;
	case COLOR_24:
		if (!ReadUByte(fp, tmp)) return FALSE;
		red = (float) tmp / (float) 255.0;
		if (!ReadUByte(fp, tmp)) return FALSE;
		green = (float) tmp / (float) 255.0;
		if (!ReadUByte(fp, tmp)) return FALSE;
		blue = (float) tmp / (float) 255.0;
		break;
	default:
		fseek(fp, chunkStart + chunk.len, SEEK_SET);
		return FALSE;
	}

	return TRUE;
}

// 读入顶点
int C3dsReader::ReadPointArray (CKnuckle*	newchild, long fileSize, FILE *fp) 
{
    unsigned short	count;
	float	value;
		
	if (!ReadUShort(fp, count)) return FALSE;
    float* x = new float[count];
	float* y = new float[count];
	float* z = new float[count];
	if (x == NULL || y == NULL || z == NULL) return FALSE;

    for (int i = 0; i<count; i++) 
	{
		if (!ReadFloat(fp, value)) 
		{	//X
			delete [] x;
			delete [] y;
			delete [] z;
			return FALSE; 
		}
		x[i] = value;
		if (!ReadFloat(fp, value)) 
		{	//Y
			delete [] x;
			delete [] y;
			delete [] z;
			return FALSE; 
		}
		y[i] = value;
		if (!ReadFloat(fp, value)) 
		{	//Z
			delete [] x;
			delete [] y;
			delete [] z;
			return FALSE; 
		}
		z[i] = value;
	}
	
	newchild->setX(x, count);
	newchild->setY(y, count);
	newchild->setZ(z, count);

    return count;
}

// 读入多边形
int C3dsReader::ReadFaceArray (CKnuckle* newchild, long unsigned fileSize, FILE* fp) 
{
    unsigned short	count = 0;
	unsigned short	value = 0;
	BOOL error = FALSE;
	
	// 读入数量
	int* fac;
	if (!ReadUShort(fp, count)) return FALSE;
	fac = new int[count*3];
	if (fac == NULL) return FALSE;
	
	
	// 读入面
	for (int i=0; i<count;i++) 
	{
		// 读入三角形面的数量
		if (!ReadUShort(fp, value)) error = TRUE;
		fac[3*i +0] = value;
		if (!ReadUShort(fp, value)) error = TRUE;
		fac[3*i +1] = value;
		if (!ReadUShort(fp, value)) error = TRUE;
		fac[3*i +2] = value;
		
		if (!ReadUShort(fp, value)) error = TRUE; // 读入可见的边

		if(error) 
		{
			delete [] fac;
			fac = NULL;
			return FALSE;
		}
	}
	

	newchild->setFaces(fac, count*3);
	return count*3;
}

// 读入对象所用的材质
int C3dsReader::ReadMeshMatGroup(CKnuckle* newchild, MaterialDict* matdict, long fileSize, FILE* fp) 
{
    
	unsigned short	count, face;
	char			name[256];
	tMaterial*		lookup;
	long			index = 0;

	// 读入材质名称
	if (!Read3DSString(fp, name, 256)) return FALSE;

	// 在材质库中查找该材质
	if ((lookup = matdict->Lookup(name)) != NULL) 
	{
		index = newchild->addMaterial(lookup);
	}
	

	// 读入该材质映射的面的数量
	if (!ReadUShort(fp, count)) return FALSE;

    while (count-- > 0) 
	{
		if (!ReadUShort(fp, face)) return FALSE;
		if (index != -1) newchild->addMaterialFace(face, index);
    }

	return TRUE;
}

// 读入对象数据
int C3dsReader::ReadTriObject(MaterialDict* matdict, long fileSize, FILE* fp, long triStart, long triSize, char* groupName)
{
	
	Chunk3DS	chunk;
	long		chunkStart = ftell(fp);
	int			verticecount = 0;
	int			facecount = 0;
	int			matcount = 0;
	static int	id = 1;
	CKnuckle*	newchild = new CKnuckle();


	// 读入并填充数据
	while (chunkStart < triStart + triSize && Read3DSChunk(fp, chunk)) 
	{
		switch (chunk.id) 
		{
		case POINT_ARRAY:
			verticecount = ReadPointArray(newchild, fileSize, fp);
			if (verticecount == FALSE) return FALSE;
			break;
		case FACE_ARRAY:
			facecount = ReadFaceArray(newchild, fileSize, fp);
			if (facecount == FALSE) return FALSE;
			break;
		case MSH_MAT_GROUP:
			if (!ReadMeshMatGroup(newchild, matdict, fileSize, fp)) return FALSE;
			break;
		default:
			// 忽略一些不需要的块
			fseek(fp, chunkStart + chunk.len, SEEK_SET);
		}
		chunkStart = ftell(fp);
	}

	
	// 设置名称，并将本项目添加到列表中
	newchild->setName(groupName);
	newchild->setId(id);
	DaList->add(newchild);
	id++;

	return TRUE;
}

// 读入对应名称的对象块，其它名称的块将忽略
int C3dsReader::ReadNamedObject(MaterialDict* matdict, long fileSize, long namedStart, long namedSize, FILE* fp)
{
	char		groupName[256];
	Chunk3DS	chunk;
	long		chunkStart;

	if (!Read3DSString(fp, groupName, 256)) return FALSE;

	chunkStart = ftell(fp);

	while (chunkStart < namedStart+namedSize &&	Read3DSChunk(fp, chunk))
	{
		switch (chunk.id) 
		{
		case N_TRI_OBJECT:
			if (!ReadTriObject(matdict, fileSize, fp, chunkStart, chunk.len, groupName)) return FALSE;
			break;
		default:
			// 忽略一些不需要的块
			fseek(fp, chunkStart + chunk.len, SEEK_SET);
		}
		chunkStart = ftell(fp);
	}

	return TRUE;
}

// 读入材质定义，并将其添加到材质库中
int C3dsReader::ReadMatEntry(MaterialDict* matdict, long fileSize, long matStart, long matSize, FILE* fp)
{
	long			chunkStart = ftell(fp);
	Chunk3DS		chunk;
	char			name[256];
	float			red, green, blue;
	float			percentage;
	tMaterial		material;


	while (chunkStart < matStart + matSize &&
		Read3DSChunk(fp, chunk)) 
	{
		switch (chunk.id) 
		{
		case MAT_NAME:
			if (!Read3DSString(fp, name, 256)) return FALSE;
			break;
		case MAT_AMBIENT:
			if (!ReadColor(fp, red, green, blue)) return FALSE;
			material.ambientColor[0] = red;
			material.ambientColor[1] = green;
			material.ambientColor[2] = blue;
			break;
		case MAT_DIFFUSE:
			if (!ReadColor(fp, red, green, blue)) return FALSE;
			material.diffuseColor[0] = red;
			material.diffuseColor[1] = green;
			material.diffuseColor[2] = blue;
			break;
		case MAT_SPECULAR:
			if (!ReadColor(fp, red, green, blue)) return FALSE;
			material.specularColor[0] = red;
			material.specularColor[1] = green;
			material.specularColor[2] = blue;
			break;
		case MAT_SHININESS:
			if (!ReadPercentage(fp, percentage)) return FALSE;
			material.shininess = ((float)percentage)/100.0f;
			break;
		case MAT_TRANSPARENCY:
			if (!ReadPercentage(fp, percentage)) return FALSE;
			material.transparency = ((float)percentage)/100.0f;
			break;
		default:
			// 忽略一些不需要的块
			fseek(fp, chunkStart + chunk.len, SEEK_SET);
		}
		chunkStart = ftell(fp);
	}

	matdict->Add(name, material);

	return TRUE;
}

// 读入最高级的对象数据
int C3dsReader::ReadMDATA(MaterialDict* matdict, long fileSize, long mdataStart, long mdataSize, FILE* fp)
{
	long			chunkStart = ftell(fp);
	Chunk3DS		chunk;
	unsigned long	version;
	float			scale;

	while (chunkStart < mdataStart + mdataSize && Read3DSChunk(fp, chunk)) 
	{
		switch (chunk.id) 
		{
		case MESH_VERSION:
			if (!ReadULong(fp, version)) 
			{
				return FALSE;
			}
			break;
		case MAT_ENTRY:
			if (!ReadMatEntry(matdict, fileSize, chunkStart, chunk.len, fp)) 
			{
				return FALSE;
			}
			break;
		case MASTER_SCALE:
			if (!ReadFloat(fp, scale)) 
			{
				return FALSE;
			}
			break;
		case NAMED_OBJECT:
			if (!ReadNamedObject(matdict, fileSize, chunkStart, chunk.len, fp)) 
			{
				return FALSE;
			}
			break;
		default:
			// 忽略一些不需要的块
			fseek(fp, chunkStart + chunk.len, SEEK_SET);
		}
		chunkStart = ftell(fp);
	}

	return TRUE;
}

// 读入3DS文件
int C3dsReader::Read3DSFile(long fileSize, long fileStart, long fileLen, FILE* fp)
{
	long			chunkStart = ftell(fp);
	Chunk3DS		chunk;
	MaterialDict	*matdict = new MaterialDict();
	unsigned long	version;

	while (chunkStart < fileStart + fileLen && Read3DSChunk(fp, chunk)) 
	{
		switch (chunk.id) 
		{
		case M3D_VERSION:
			if (!ReadULong(fp, version)) goto error;
			break;
		case MDATA:
			if (!ReadMDATA(matdict, fileSize, chunkStart, chunk.len, fp)) goto error;
			break;
		case KFDATA:
			if (!ReadKFDATA(fileSize, chunkStart, chunk.len, fp)) goto error;
			break;
		default:
			// 忽略一些不需要的块
			fseek(fp, chunkStart + chunk.len, SEEK_SET);
		}
		chunkStart = ftell(fp);
	}
	
	if (matdict != NULL) delete matdict;
	return TRUE;

error:
	if (matdict != NULL) delete matdict;
	return FALSE;
}

// 验证当前的文件是否是3DS文件
int C3dsReader::Is3DSFile(FILE* fp)
{
	Chunk3DS	chunk;
	long		pos = ftell(fp);

	if (!Read3DSChunk(fp, chunk)) 
	{
		fseek(fp, pos, SEEK_SET);
		return FALSE;
	}

	fseek(fp, pos, SEEK_SET);
	return (chunk.id == M3DMAGIC);
}

// 读入一个3DS文件
BOOL C3dsReader::Reader( char* filename, CRobotHand* _list)
{
	FILE*		fp;
	long		fileSize;
	Chunk3DS	chunk;
	DaList = _list;

	// 以“二进制”的方式打开一个3DS文件
	if ((fp = fopen(filename, "rb")) != NULL) 
	{
		long	chunkStart = ftell(fp);

		// 获得文件大小
		fseek(fp, 0, SEEK_END);
		fileSize = ftell(fp);
		fseek(fp, 0, SEEK_SET);

		// 验证文件类型
		if (!Is3DSFile(fp)) 
		{
				return FALSE;
		}

		// 循环所有的块
		while (chunkStart < fileSize &&
			Read3DSChunk(fp, chunk)) 
		{
			switch (chunk.id) 
			{
			case M3DMAGIC:
				if (!Read3DSFile(fileSize, chunkStart, chunk.len, fp)) 
				{
					fclose(fp);
					return FALSE;
				}
				break;
			default:
				// 忽略一些不需要的块
				fseek(fp, chunkStart + chunk.len, SEEK_SET);
			}
			chunkStart = ftell(fp);
		}

		fclose(fp);
	}
	else 
		return FALSE;


	return TRUE;
}



int C3dsReader::ReadKFDATA(long fileSize, long kfdataStart, long kfdataSize, FILE * fp)
{
	long		chunkStart = ftell(fp);
	Chunk3DS	chunk;
	short		version;
	long		kflength;
	long		kfstart;
	long		kfend;
	char		name[256];


	while (chunkStart < kfdataStart + kfdataSize && Read3DSChunk(fp, chunk)) 
	{
		switch (chunk.id) 
		{
		case KFHDR:
			if (!ReadShort(fp,version)) return FALSE;
			if (!Read3DSString(fp, name, 256)) return FALSE;
			if (!ReadLong(fp, kflength)) return FALSE;
			break;
		case KFSEG:
			if (!ReadLong(fp, kfstart)) return FALSE;
			if (!ReadLong(fp, kfend)) return FALSE;

			break;
		case OBJECT_NODE_TAG:
			ReadKFObjectNode(fileSize, chunkStart, chunk.len, fp);
			fseek(fp, chunkStart + chunk.len, SEEK_SET);
			break;
		default:
			// 忽略一些不需要的块
			fseek(fp, chunkStart + chunk.len, SEEK_SET);
		}
		chunkStart = ftell(fp);
	}

	return TRUE;
}

int C3dsReader::ReadKFObjectNode(long fileSize, long nodeStart, long nodeSize, FILE * fp)
{
	
	long		chunkStart = ftell(fp);
	Chunk3DS	chunk;
	short		nodeid;
	char		nodeName[256];
	tVector		pivot;

	while (chunkStart < nodeStart + nodeSize && Read3DSChunk(fp, chunk)) 
	{
		switch (chunk.id) 
		{
		case NODE_ID:
			if(!ReadShort(fp, nodeid)) return false;
			fseek(fp, chunkStart + chunk.len, SEEK_SET);
			break;
		case NODE_HDR:
			if (!Read3DSString(fp, nodeName, 256)) return FALSE;
			fseek(fp, chunkStart + chunk.len, SEEK_SET);
			break;
		case PIVOT:
			if (!ReadFloat(fp, pivot.x)) return FALSE;
			if (!ReadFloat(fp, pivot.y)) return FALSE;
			if (!ReadFloat(fp, pivot.z)) return FALSE;
			fseek(fp, chunkStart + chunk.len, SEEK_SET);
			break;
		case POS_TRACK_TAG:
			if(!ReadKFTrackTag(fileSize, chunkStart, chunk.len, fp,  nodeName, &pivot, chunk)) return FALSE;
			fseek(fp, chunkStart + chunk.len, SEEK_SET);			
			break;
		case ROT_TRACK_TAG:
			if(!ReadKFTrackTag(fileSize, chunkStart, chunk.len, fp,  nodeName, &pivot, chunk)) return FALSE;
			fseek(fp, chunkStart + chunk.len, SEEK_SET);			
			break;
		case SCL_TRACK_TAG:
			if(!ReadKFTrackTag(fileSize, chunkStart, chunk.len, fp,  nodeName, &pivot, chunk)) return FALSE;
			fseek(fp, chunkStart + chunk.len, SEEK_SET);			
			break;
		default:
			// 忽略一些不需要的块
			fseek(fp, chunkStart + chunk.len, SEEK_SET);
		}
		chunkStart = ftell(fp);
	}

	return TRUE;
}

int C3dsReader::ReadKFTrackTag(long fileSize, long tagStart, long tagSize, FILE * fp, char * nodeName, tVector* pivot, Chunk3DS	chunk)
{
	long  numkeys;
	short rflags;
	short trflags;
	long  trtmin,trtmax;
	CKnuckle* current;
	Key key;

	// 获得当前的物体
	current = DaList->getObjectByName(nodeName);
	if(current == NULL) return FALSE;
	// 设置转动轴
	current->setPivotPoint(pivot);

	ReadShort(fp, trflags);
	ReadLong(fp,  trtmin);
	ReadLong(fp,  trtmax);
	ReadLong(fp,  numkeys);

	for (int i=0; i<numkeys; i++) 
	{  
		memset(&key,0,sizeof(Key));
		ReadLong(fp, key.time); 
		ReadShort(fp, rflags);
 		if (rflags&W_TENS) ReadFloat(fp, key.tension);
 		if (rflags&W_CONT) ReadFloat(fp, key.continuity);
 		if (rflags&W_BIAS) ReadFloat(fp, key.bias);
 		if (rflags&W_EASETO) ReadFloat(fp, key.easeto);
 		if (rflags&W_EASEFROM)ReadFloat(fp, key.easefrom);
		switch (chunk.id) 
		{
			case POS_TRACK_TAG:	
				Poskey pkey;
				memset(&pkey,0,sizeof(Poskey));
				memcpy(&pkey,&key,sizeof(Poskey));
				ReadFloat(fp, pkey.pos[0]);
				ReadFloat(fp, pkey.pos[1]);
				ReadFloat(fp, pkey.pos[2]);

				break;
			case SCL_TRACK_TAG:	
				Poskey skey;
				memset(&skey,0,sizeof(Poskey));
				memcpy(&skey,&key,sizeof(Poskey));
				ReadFloat(fp, skey.pos[0]);
				ReadFloat(fp, skey.pos[1]);
				ReadFloat(fp, skey.pos[2]);

				break;								
			case ROT_TRACK_TAG: 
				Rotkey rkey;
				memset(&rkey,0,sizeof(Rotkey));
				memcpy(&rkey,&key,sizeof(Rotkey));
				ReadFloat(fp, rkey.angle);
				ReadFloat(fp, rkey.axis[0]);
				ReadFloat(fp, rkey.axis[1]);
				ReadFloat(fp, rkey.axis[2]);

				break;
		}  
	}	

	return TRUE;
}
