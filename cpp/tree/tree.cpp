// main.cpp

#include <iostream>

using namespace std;

class CNode  
{
public:
	CNode( int value = 0 );
	virtual ~CNode();

	void SetValue( int value ) ;
	int GetValue() const ;

	bool   AddChild( int value ) ;
	CNode& GetChild( int idx ) const ;

//	friend std::ostream& operator<<( std::ostream& os, const CNode& node )  ;

	int  GetNumChildren() const ;

private: 
	int _numChildren ;
	int _value ;

	enum{ MAX_CHILDREN = 10 } ;
	CNode* _child[ MAX_CHILDREN ] ;
};

std::ostream& operator<<( std::ostream& os, const CNode& node )  ;


CNode::CNode( int value )
: _numChildren( 0 )
, _value( value )
{

}

CNode::~CNode()
{

}


int CNode::GetNumChildren() const
{
	return _numChildren ;
}


int CNode::GetValue() const
{
	return _value ;
}


CNode& CNode::GetChild( int idx ) const
{
	return *_child[ idx ] ;
}


void CNode::SetValue( int value )
{
	_value = value ;
}


bool CNode::AddChild( int value )
{
	if( _numChildren >= MAX_CHILDREN )
	{
		return false ;
	}

	_child[ _numChildren ] = new CNode( value ) ;

	_numChildren++ ;

	return true ;
}



ostream& operator<<( std::ostream& os, const CNode& node )
{
	os << node.GetValue() << endl ;

	int max = node.GetNumChildren() ;
	for( int idx = 0 ; idx < max ; idx++ )
	{
		const CNode& child = node.GetChild( idx ) ;

		os << child ;
	}

	return os ;
}


int main( int argc , char** argv )
{
	CNode parent(1) ;

	parent.AddChild( 11 ) ;
	parent.AddChild( 12 ) ;
	parent.AddChild( 13 ) ;

	cout << parent ;

	cin.get() ;	// wait for enter key press

 	return 0 ;
}

