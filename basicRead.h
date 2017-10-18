/////////////////////////////////////////////////////////////////////////////
// 
//                各种数据的读入函数
//
/////////////////////////////////////////////////////////////////////////////


#ifndef BASICREAD_H
#define BASICREAD_H

inline short ReadByte(FILE* fp, char& value) 
{return (fread(&value, sizeof(value), 1, fp) == 1);}

inline short ReadUByte(FILE* fp, unsigned char& value) 
{return (fread(&value, sizeof(value), 1, fp) == 1);}

inline short ReadShort(FILE* fp, short& value) 
{return (fread(&value, sizeof(value), 1, fp) == 1);}

inline short ReadUShort(FILE* fp, unsigned short& value) 
{return (fread(&value, sizeof(value), 1, fp) == 1);}

inline short ReadLong(FILE* fp, long& value) 
{return (fread(&value, sizeof(value), 1, fp) == 1);}

inline short ReadULong(FILE* fp, unsigned long& value) 
{return (fread(&value, sizeof(value), 1, fp) == 1);}

inline short ReadFloat(FILE* fp, float& value) 
{return (fread(&value, sizeof(value), 1, fp) == 1);}

inline short ReadDouble(FILE* fp, double& value) 
{return (fread(&value, sizeof(value), 1, fp) == 1);}

#endif