/*
 * Matrix4Wrapper.cpp
 *
 *  Created on: 6 мая 2015
 *      Author: vadim
 */

#include "MatrixWrapper.h"
#include <cstring>

Matrix4Wrapper::Matrix4Wrapper()
{
}

Matrix4Wrapper::~Matrix4Wrapper()
{
}

Matrix4Wrapper::Matrix4Wrapper( const Matrix4Wrapper & src )
{
	setRaw( src.getRaw() );
}

Matrix4Wrapper & Matrix4Wrapper::operator == ( const Matrix4Wrapper & src )
{
	if( this == &src )
	{
		return *this;
	}

	setRaw( src.getRaw() );

	return *this;
}

void Matrix4Wrapper::setRaw( const float * mat )
{
	memcpy( m_Raw, mat, sizeof( m_Raw ) );
}

const float * Matrix4Wrapper::getRaw() const
{
	return m_Raw;
}

Matrix4Wrapper::operator float *()
{
	return const_cast<float *>( getRaw() );
}
















