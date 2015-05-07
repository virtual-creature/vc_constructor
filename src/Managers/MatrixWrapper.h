/*
 * Matrix4Wrapper.h
 *
 *  Created on: 6 мая 2015
 *      Author: vadim
 */

#ifndef MANAGERS_Matrix4Wrapper_H_
#define MANAGERS_Matrix4Wrapper_H_

#include <vector>

class Matrix4Wrapper
{
	typedef float Matrix4[16];
public:
	Matrix4Wrapper();
	Matrix4Wrapper( const Matrix4Wrapper & src );
	operator float *();
	Matrix4Wrapper & operator == ( const Matrix4Wrapper & src );
	virtual ~Matrix4Wrapper();

	const float * getRaw() const;

private:

	void setRaw( const float * mat );

	Matrix4 m_Raw;

	std::vector<Matrix4> a;

};

#endif /* MANAGERS_Matrix4Wrapper_H_ */
