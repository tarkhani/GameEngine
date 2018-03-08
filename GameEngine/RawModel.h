#pragma once
class RawModel
{
public:

	RawModel(int VaoID,int Indexcount);
	RawModel( RawModel& A):Indexcount(A.Indexcount),VaoID(A.VaoID){
	};
	int getIndexcount() { return Indexcount; };
	int getVaoID() { return VaoID; };
	
	
private :

	int Indexcount;
	int VaoID;

};

