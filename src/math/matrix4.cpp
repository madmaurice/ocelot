
#include "matrix4.h"
#include "vector3.h"
#include "vector4.h"
#include <cmath>
#include <cstring>

OC_NS_BG;

Matrix4::Matrix4()
{
}

Matrix4::Matrix4(bool toZero)
{
	if (toZero)
		memset(m_data, 0, 4*4*sizeof(float));
}

Matrix4::Matrix4( const Matrix4& matrix )
{
    memcpy( m_data, (void*)&matrix, 16*sizeof(float) );
}

Matrix4::Matrix4(float m11, float m12, float m13, float m14,
				 float m21, float m22, float m23, float m24,
				 float m31, float m32, float m33, float m34,
				 float m41, float m42, float m43, float m44)
{
	m_data[ 0] = m11;
	m_data[ 1] = m12;
	m_data[ 2] = m13;
	m_data[ 3] = m14;

	m_data[ 4] = m21;
	m_data[ 5] = m22;
	m_data[ 6] = m23;
	m_data[ 7] = m24;

	m_data[ 8] = m31;
	m_data[ 9] = m32;
	m_data[10] = m33;
	m_data[11] = m34;

	m_data[12] = m41;
	m_data[13] = m42;
	m_data[14] = m43;
	m_data[15] = m44;
}

Matrix4& Matrix4::operator= (const Matrix4& matrix)
{
    if (this == &matrix)
    {
        return *this;
    }

    memcpy( m_data, matrix.m_data, 16*sizeof(float) );
    return *this;
}

void Matrix4::rotationX(float radians)
{
    float sin = sinf( radians );
	float cos = cosf( radians );

	m_data[ 0] = 1.0f;
	m_data[ 1] = 0.0f;
	m_data[ 2] = 0.0f;
	m_data[ 3] = 0.0f;

	m_data[ 4] = 0.0f;
	m_data[ 5] = cos;
	m_data[ 6] = sin;
	m_data[ 7] = 0.0f;

	m_data[ 8] = 0.0f;
	m_data[ 9] = -sin;
	m_data[10] = cos;
	m_data[11] = 0.0f;

	m_data[12] = 0.0f;
	m_data[13] = 0.0f;
	m_data[14] = 0.0f;
	m_data[15] = 1.0f;
}

void Matrix4::rotationY(float radians)
{
	float sin = sinf(radians);
	float cos = cosf(radians);

	m_data[ 0] = cos;
	m_data[ 1] = 0.0f;
	m_data[ 2] = -sin;
	m_data[ 3] = 0.0f;

	m_data[ 4] = 0.0f;
	m_data[ 5] = 1.0f;
	m_data[ 6] = 0.0f;
	m_data[ 7] = 0.0f;

	m_data[ 8] = sin;
	m_data[ 9] = 0.0f;
	m_data[10] = cos;
	m_data[11] = 0.0f;

	m_data[12] = 0.0f;
	m_data[13] = 0.0f;
	m_data[14] = 0.0f;
	m_data[15] = 1.0f;
}

void Matrix4::rotationZ(float radians)
{
	float sin = sinf( radians );
	float cos = cosf( radians );

	m_data[ 0] = cos;
	m_data[ 1] = sin;
	m_data[ 2] = 0.0f;
	m_data[ 3] = 0.0f;

	m_data[ 4] = -sin;
	m_data[ 5] = cos;
	m_data[ 6] = 0.0f;
	m_data[ 7] = 0.0f;

	m_data[ 8] = 0.0f;
	m_data[ 9] = 0.0f;
	m_data[10] = 1.0f;
	m_data[11] = 0.0f;

	m_data[12] = 0.0f;
	m_data[13] = 0.0f;
	m_data[14] = 0.0f;
	m_data[15] = 1.0f;
}

void Matrix4::scale(float fScale)
{
	m_data[ 0] = fScale;
	m_data[ 1] = 0.0f;
	m_data[ 2] = 0.0f;
	m_data[ 3] = 0.0f;

	m_data[ 4] = 0.0f;
	m_data[ 5] = fScale;
	m_data[ 6] = 0.0f;
	m_data[ 7] = 0.0f;

	m_data[ 8] = 0.0f;
	m_data[ 9] = 0.0f;
	m_data[10] = fScale;
	m_data[11] = 0.0f;

	m_data[12] = 0.0f;
	m_data[13] = 0.0f;
	m_data[14] = 0.0f;
	m_data[15] = 1.0f;
}

void Matrix4::translate(float x, float y, float z)
{
	m_data[ 0] = 1.0f;
	m_data[ 1] = 0.0f;
	m_data[ 2] = 0.0f;
	m_data[ 3] = 0.0f;

	m_data[ 4] = 0.0f;
	m_data[ 5] = 1.0f;
	m_data[ 6] = 0.0f;
	m_data[ 7] = 0.0f;

	m_data[ 8] = 0.0f;
	m_data[ 9] = 0.0f;
	m_data[10] = 1.0f;
	m_data[11] = 0.0f;

	m_data[12] = x;
	m_data[13] = y;
	m_data[14] = z;
	m_data[15] = 1.0f;
}

Matrix4 Matrix4::inverse() const
{
    float a0 = m_data[ 0]*m_data[ 5] - m_data[ 1]*m_data[ 4];
    float a1 = m_data[ 0]*m_data[ 6] - m_data[ 2]*m_data[ 4];
    float a2 = m_data[ 0]*m_data[ 7] - m_data[ 3]*m_data[ 4];
    float a3 = m_data[ 1]*m_data[ 6] - m_data[ 2]*m_data[ 5];
    float a4 = m_data[ 1]*m_data[ 7] - m_data[ 3]*m_data[ 5];
    float a5 = m_data[ 2]*m_data[ 7] - m_data[ 3]*m_data[ 6];
    float b0 = m_data[ 8]*m_data[13] - m_data[ 9]*m_data[12];
    float b1 = m_data[ 8]*m_data[14] - m_data[10]*m_data[12];
    float b2 = m_data[ 8]*m_data[15] - m_data[11]*m_data[12];
    float b3 = m_data[ 9]*m_data[14] - m_data[10]*m_data[13];
    float b4 = m_data[ 9]*m_data[15] - m_data[11]*m_data[13];
    float b5 = m_data[10]*m_data[15] - m_data[11]*m_data[14];

    float fDet = a0*b5 - a1*b4 + a2*b3 + a3*b2 - a4*b1 + a5*b0;

    Matrix4 kInv;
    kInv(0,0) = + m_data[ 5]*b5 - m_data[ 6]*b4 + m_data[ 7]*b3;
    kInv(1,0) = - m_data[ 4]*b5 + m_data[ 6]*b2 - m_data[ 7]*b1;
    kInv(2,0) = + m_data[ 4]*b4 - m_data[ 5]*b2 + m_data[ 7]*b0;
    kInv(3,0) = - m_data[ 4]*b3 + m_data[ 5]*b1 - m_data[ 6]*b0;
    kInv(0,1) = - m_data[ 1]*b5 + m_data[ 2]*b4 - m_data[ 3]*b3;
    kInv(1,1) = + m_data[ 0]*b5 - m_data[ 2]*b2 + m_data[ 3]*b1;
    kInv(2,1) = - m_data[ 0]*b4 + m_data[ 1]*b2 - m_data[ 3]*b0;
    kInv(3,1) = + m_data[ 0]*b3 - m_data[ 1]*b1 + m_data[ 2]*b0;
    kInv(0,2) = + m_data[13]*a5 - m_data[14]*a4 + m_data[15]*a3;
    kInv(1,2) = - m_data[12]*a5 + m_data[14]*a2 - m_data[15]*a1;
    kInv(2,2) = + m_data[12]*a4 - m_data[13]*a2 + m_data[15]*a0;
    kInv(3,2) = - m_data[12]*a3 + m_data[13]*a1 - m_data[14]*a0;
    kInv(0,3) = - m_data[ 9]*a5 + m_data[10]*a4 - m_data[11]*a3;
    kInv(1,3) = + m_data[ 8]*a5 - m_data[10]*a2 + m_data[11]*a1;
    kInv(2,3) = - m_data[ 8]*a4 + m_data[ 9]*a2 - m_data[11]*a0;
    kInv(3,3) = + m_data[ 8]*a3 - m_data[ 9]*a1 + m_data[10]*a0;

    float fInvDet = ((float)1.0)/fDet;
    for (uint32 row = 0; row < 4; row++)
    {
        for (uint32 col = 0; col < 4; col++)
            kInv(row,col) *= fInvDet;
    }

    return kInv;
}

Vector3 Matrix4::getBasisX() const
{
	Vector3 basis;

	for (uint32 i = 0; i < 3; i++)
        basis[i] = m_data[index(0,i)];
	
	return basis;
}

Vector3 Matrix4::getBasisY() const
{
	Vector3 basis;

	for (uint32 i = 0; i < 3; i++)
        basis[i] = m_data[index(1,i)];
	
	return basis;
}

Vector3 Matrix4::getBasisZ() const
{
	Vector3 basis;

	for (uint32 i = 0; i < 3; i++)
        basis[i] = m_data[index(2,i)];
	
	return basis;
}

Vector3 Matrix4::getTranslation() const
{
	Vector3 pos;

	for (uint32 i = 0; i < 3; i++)
		pos[i] = m_data[index(3,i)];

	return pos;
}

void Matrix4::setTranslation(const Vector3& trans)
{
	for (uint32 i = 0; i < 3; i++)
		m_data[index(3,i)] = trans[i];
}

Matrix3 Matrix4::getRotation() const
{
	Matrix3 matrix;

	matrix.setRow( 0, getBasisX() );
	matrix.setRow( 1, getBasisY() );
	matrix.setRow( 2, getBasisZ() );

	return matrix;
}

void Matrix4::setRotation(const Matrix3& rot)
{
	for (uint32 i = 0; i < 3; i++)
		for (uint32 j = 0; j < 3; j++)
            m_data[index(i,j)] = rot[(3*i+j)];
}

Matrix4 Matrix4::rotationMatrixX(float radians)
{
	Matrix4 ret;
	ret.rotationX(radians);
	return ret;
}

Matrix4 Matrix4::rotationMatrixY(float radians)
{
	Matrix4 ret;
	ret.rotationY(radians);
	return ret;
}

Matrix4 Matrix4::rotationMatrixZ(float radians)
{
	Matrix4 ret;
	ret.rotationZ(radians);
	return ret;
}

Matrix4 Matrix4::scaleMatrix(float scale)
{
	Matrix4 ret;
	ret.scale(scale);
	return ret;
}

Matrix4 Matrix4::scaleMatrix(const Vector3& scale)
{
	Matrix4 ret;

	ret.m_data[ 0] = scale.x;
	ret.m_data[ 1] = 0.0f;
	ret.m_data[ 2] = 0.0f;
	ret.m_data[ 3] = 0.0f;

	ret.m_data[ 4] = 0.0f;
	ret.m_data[ 5] = scale.y;
	ret.m_data[ 6] = 0.0f;
	ret.m_data[ 7] = 0.0f;

	ret.m_data[ 8] = 0.0f;
	ret.m_data[ 9] = 0.0f;
	ret.m_data[10] = scale.z;
	ret.m_data[11] = 0.0f;

	ret.m_data[12] = 0.0f;
	ret.m_data[13] = 0.0f;
	ret.m_data[14] = 0.0f;
	ret.m_data[15] = 1.0f;
	
	return ret;
}

Matrix4 Matrix4::scaleMatrixXYZ(float x, float y, float z)
{
	Matrix4 ret;

	ret.m_data[ 0] = x;
	ret.m_data[ 1] = 0.0f;
	ret.m_data[ 2] = 0.0f;
	ret.m_data[ 3] = 0.0f;

	ret.m_data[ 4] = 0.0f;
	ret.m_data[ 5] = y;
	ret.m_data[ 6] = 0.0f;
	ret.m_data[ 7] = 0.0f;

	ret.m_data[ 8] = 0.0f;
	ret.m_data[ 9] = 0.0f;
	ret.m_data[10] = z;
	ret.m_data[11] = 0.0f;

	ret.m_data[12] = 0.0f;
	ret.m_data[13] = 0.0f;
	ret.m_data[14] = 0.0f;
	ret.m_data[15] = 1.0f;
	
	return ret;
}

Matrix4 Matrix4::translationMatrix(float x, float y, float z)
{
	Matrix4 ret;
	ret.translate(x, y, z);
	return ret;
}

Matrix4 Matrix4::lookAtLHMatrix(Vector3& eye, Vector3& at, Vector3& up)
{
	// This method is based on the method of the same name from the D3DX library.

	Matrix4 ret;

	Vector3 zaxis = at - eye; 
	zaxis.normalize();
	
	Vector3 xaxis = up.cross(zaxis);
	xaxis.normalize();

	Vector3 yaxis = zaxis.cross(xaxis);

	ret.m_data[ 0] = xaxis.x;
	ret.m_data[ 1] = yaxis.x;
	ret.m_data[ 2] = zaxis.x;
	ret.m_data[ 3] = 0.0f;

	ret.m_data[ 4] = xaxis.y;
	ret.m_data[ 5] = yaxis.y;
	ret.m_data[ 6] = zaxis.y;
	ret.m_data[ 7] = 0.0f;

	ret.m_data[ 8] = xaxis.z;
	ret.m_data[ 9] = yaxis.z;
	ret.m_data[10] = zaxis.z;
	ret.m_data[11] = 0.0f;

	ret.m_data[12] = -(xaxis.dot(eye));
	ret.m_data[13] = -(yaxis.dot(eye));
	ret.m_data[14] = -(zaxis.dot(eye));
	ret.m_data[15] = 1.0f;

	return ret;
}

Matrix4 Matrix4::perspectiveFovLHMatrix(float fovy, float aspect, float zn, float zf)
{
	// This method is based on the method of the same name from the D3DX library.

	Matrix4 ret;

	float tanY = tan( fovy / 2.0f );
	if ( 0.0f == tanY ) tanY = 0.001f;
	float yScale = 1.0f / tanY;

	if ( 0.0f == aspect ) aspect = 0.001f;
	float xScale = yScale / aspect;

	ret.m_data[ 0] = xScale;
	ret.m_data[ 1] = 0.0f;
	ret.m_data[ 2] = 0.0f;
	ret.m_data[ 3] = 0.0f;

	ret.m_data[ 4] = 0.0f;
	ret.m_data[ 5] = yScale;
	ret.m_data[ 6] = 0.0f;
	ret.m_data[ 7] = 0.0f;

	ret.m_data[ 8] = 0.0f;
	ret.m_data[ 9] = 0.0f;
	ret.m_data[10] = zf / ( zf-zn );
	ret.m_data[11] = 1.0f;

	ret.m_data[12] = 0.0f;
	ret.m_data[13] = 0.0f;
	ret.m_data[14] = -zn*zf / ( zf-zn );
	ret.m_data[15] = 0.0f;

	return ret;
}

Matrix4 Matrix4::orthographicLHMatrix(float zn, float zf, float width, float height)
{
	// This method is based on the method of the same name from the D3DX library.

	Matrix4 ret;


	if ( zn == zf ) zf = zn + 0.1f;
	if ( width <= 0.0f ) width = 1.0f;
	if ( height <= 0.0f ) height = 1.0f;

	ret.m_data[ 0] = 2.0f / width;
	ret.m_data[ 1] = 0.0f;
	ret.m_data[ 2] = 0.0f;
	ret.m_data[ 3] = 0.0f;

	ret.m_data[ 4] = 0.0f;
	ret.m_data[ 5] = 2.0f / height;
	ret.m_data[ 6] = 0.0f;
	ret.m_data[ 7] = 0.0f;

	ret.m_data[ 8] = 0.0f;
	ret.m_data[ 9] = 0.0f;
	ret.m_data[10] = 1.0f / ( zf-zn );
	ret.m_data[11] = 0.0f;

	ret.m_data[12] = 0.0f;
	ret.m_data[13] = 0.0f;
	ret.m_data[14] = zn / ( zn-zf );
	ret.m_data[15] = 1.0f;

	return ret;
}

float Matrix4::operator[] (uint32 iPos) const
{
    return m_data[iPos];
}

float& Matrix4::operator[] (uint32 iPos)
{
    return m_data[iPos];
}

float Matrix4::operator() (uint32 row, uint32 col) const
{
    return m_data[index(row,col)];
}

float& Matrix4::operator() (uint32 row, uint32 col)
{
    return m_data[index(row,col)];
}

bool Matrix4::operator== (const Matrix4& matrix) const
{
    return( memcmp( m_data, matrix.m_data, 4*4*sizeof(float) ) == 0 );
}

bool Matrix4::operator!= (const Matrix4& matrix) const
{
    return( memcmp( m_data, matrix.m_data, 4*4*sizeof(float) ) != 0 );
}

Matrix4 Matrix4::operator* (const Matrix4& matrix) const
{
	Matrix4 prod;

	for (uint32 row = 0; row < 4; row++)
	{
		for (uint32 col = 0; col < 4; col++)
		{
			uint32 i = index(row, col);
			prod.m_data[i] = 0.0f;
			for (uint32 mid = 0; mid < 4; mid++)
			{
				prod.m_data[i] += 
					m_data[index(row, mid)] * matrix.m_data[index(mid, col)];
			}
		}
	}
	return prod;
}

Matrix4 Matrix4::operator+ (const Matrix4& matrix) const
{
	Matrix4 sum;

	for (uint32 i = 0; i < 4*4; i++)
		sum.m_data[i] = m_data[i] + matrix.m_data[i];

	return sum;
}

Matrix4 Matrix4::operator- (const Matrix4& matrix) const
{
	Matrix4 diff;

	for (uint32 i = 0; i < 4*4; i++)
		diff.m_data[i] = m_data[i] - matrix.m_data[i];

	return diff;
}

Matrix4 Matrix4::operator* (float scalar) const
{
	Matrix4 prod;

	for (uint32 i = 0; i < 4*4; i++)
		prod.m_data[i] = m_data[i] * scalar;

	return prod;
}

Matrix4 Matrix4::operator/ (float scalar) const
{
	Matrix4 quot;
	if (scalar != 0.0f)
	{
		float invScalar = 1.0f / scalar;
		for (uint32 i = 0; i < 4*4; i++)
			quot.m_data[i] = m_data[i] * invScalar;
	}
	else
	{
		for (uint32 i = 0; i < 4*4; i++)
			quot.m_data[i] = 0;
	}

	return quot;
}

Matrix4 Matrix4::operator- () const
{
	Matrix4 neg;

	for ( uint32 i = 0; i < 4*4; i++ )
		neg.m_data[i] = -m_data[i];

	return neg;
}

Matrix4& Matrix4::operator+= (const Matrix4& matrix)
{
	for ( uint32 i = 0; i < 4*4; i++ )
		m_data[i] += matrix.m_data[i];

	return *this;
}

Matrix4& Matrix4::operator-= (const Matrix4& matrix)
{
	for ( uint32 i = 0; i < 4*4; i++ )
		m_data[i] -= matrix.m_data[i];

	return *this;
}

Matrix4& Matrix4::operator*= (float scalar)
{
	for ( uint32 i = 0; i < 4*4; i++ )
		m_data[i] *= scalar;

	return *this;
}

Matrix4& Matrix4::operator*= (const Matrix4& matrix)
{
	Matrix4 prod = *this; 
	
	for ( uint32 row = 0; row < 4; row++ )
	{
		for ( uint32 col = 0; col < 4; col++ )
		{
			uint32 i = index(row, col);
			m_data[i] = 0.0f;
			for ( uint32 mid = 0; mid < 4; mid++ )
			{
				m_data[i] += 
					prod.m_data[index(row, mid)] * matrix.m_data[index(mid, col)];
			}
		}
	}
	return *this;
}

Matrix4& Matrix4::operator/= (float scalar)
{
	if ( scalar != 0.0f )
	{
		float invScalar = 1.0f / scalar;	
		for (uint32 i = 0; i < 4*4; i++)
			m_data[i] *= invScalar;
	}
	else
	{
		for ( uint32 i = 0; i < 4*4; i++ )
			m_data[i] = 0;
	}

	return *this;
}

void Matrix4::setZero()
{
	memset( m_data,0,4*4*sizeof(float) );
}

void Matrix4::setIdentity()
{
	for ( uint32 row = 0; row < 4; row++ ) 
	{
		for ( uint32 col = 0; col < 4; col++ )
		{
			if ( row == col )
                m_data[index(row,col)] = 1.0f;
			else
				m_data[index(row,col)] = 0.0f;
		}
	}
}

void Matrix4::setTranspose()
{
	Matrix4 mTranspose;

	for ( uint32 row = 0; row < 4; row++ )
	{
		for ( uint32 col = 0; col < 4; col++ )
			mTranspose.m_data[index(row,col)] = m_data[index(col,row)];
	}
    
	memcpy( m_data, mTranspose.m_data, 4*4*sizeof(float) );
}

Matrix4 Matrix4::zero()
{
	Matrix4 matrix = Matrix4( true );

	return matrix;
}

Matrix4 Matrix4::identity()
{
    return Matrix4(1.0f, 0.0f, 0.0f, 0.0f,
                   0.0f, 1.0f, 0.0f, 0.0f,
                   0.0f, 0.0f, 1.0f, 0.0f,
                   0.0f, 0.0f, 0.0f, 1.0f);
}

Matrix4 Matrix4::transpose()
{
	Matrix4 transpose;

	for ( uint32 row = 0; row < 4; row++ )
	{
		for ( uint32 col = 0; col < 4; col++ )
			transpose.m_data[index(row,col)] = m_data[index(col,row)];
	}

	return transpose;
}

uint32 Matrix4::index(uint32 row, uint32 col)
{
    return (4*row + col);
}

Vector4 Matrix4::operator* (const Vector4& vector) const
{
    Vector4 prod;
    for ( uint32 col = 0; col < 4; col++ )
    {
        prod[col] = 0.0f;
        for ( uint32 row = 0; row < 4; row++ )
            prod[col] += m_data[index(row,col)] * vector[row];
    }
    return prod;
}

void Matrix4::setRow(uint32 row, const Vector4& vector)
{
	for ( uint32 col = 0; col < 4; col++ )
        m_data[index(row,col)] = vector[col];
}

void Matrix4::setRow(uint32 row, const Vector3& vector)
{
    for ( uint32 col = 0; col < 3; col++ )
        m_data[index(row,col)] = vector[col];
}

Vector4 Matrix4::getRow(uint32 row) const
{
	Vector4 vector;
	for ( uint32 col = 0; col < 4; col++ )
        vector[col] = m_data[index(row,col)];

	return vector;
}

void Matrix4::setColumn(uint32 col, const Vector4& vector)
{
	for ( uint32 row = 0; row < 4; row++ )
        m_data[index(row,col)] = vector[row];
}

Vector4 Matrix4::getColumn(uint32 col) const
{
	Vector4 vector;
	for ( uint32 row = 0; row < 4; row++ )
		vector[row] = m_data[index(row,col)];

	return vector;
}

OC_NS_END;