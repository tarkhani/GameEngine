#pragma once
class RawModel
{
public:

	RawModel(int VaoID,int Indexcount);
	RawModel();
	const RawModel(const RawModel& A):Indexcount(A.Indexcount),VaoID(A.VaoID){
	};

	int getIndexcount() { return Indexcount; };
	int getVaoID()const { return VaoID; };
	
	
private :

	int Indexcount;
	int VaoID;

};

