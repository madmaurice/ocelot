
#include "matrix3.h"
#include <cstring>
#include <cmath>

OC_NS_BG;

Matrix3::Matrix3()
{
}

Matrix3::Matrix3(bool toZero)
{
	if (toZero)
		memset(m_data, 0, 9*sizeof(float));
}

Matrix3::Matrix3(const Matrix3& matrix)
{
    memcpy(m_data, (void*)&matrix, 9*sizeof(float));
}

Matrix3::Matrix3(float m11, float m12, float m13,
				 float m21, float m22, float m23,
				 float m31, float m32, float m33)
{
	m_data[0] = m11;
	m_data[1] = m12;
	m_data[2] = m13;

	m_data[3] = m21;
	m_data[4] = m22;
	m_data[5] = m23;

	m_data[6] = m31;
	m_data[7] = m32;
	m_data[8] = m33;
}

Matrix3& Matrix3::operator= (const Matrix3& matrix)
{
    if (this == &matrix)
    {
        return *this;
    }

    memcpy(m_data, matrix.m_data, 9*sizeof(float));
    return *this;
}

void Matrix3::rotationX(float radians)
{
    float sin = sinf(radians);
	float cos = cosf(radians);

	m_data[0] = 1.0f;
	m_data[1] = 0.0f;
	m_data[2] = 0.0f;

	m_data[3] = 0.0f;
	m_data[4] = cos;
	m_data[5] = sin;

	m_data[6] = 0.0f;
	m_data[7] = -sin;
	m_data[8] = cos;
}

void Matrix3::rotationY(float radians)
{
	float sin = sinf(radians);
	float cos = cosf(radians);

	m_data[0] = cos;
	m_data[1] = 0.0f;
	m_data[2] = -sin;

	m_data[3] = 0.0f;
	m_data[4] = 1.0f;
	m_data[5] = 0.0f;

	m_data[6] = sin;
	m_data[7] = 0.0f;
	m_data[8] = cos;
}

void Matrix3::rotationZ(float radians)
{
	float sin = sinf(radians);
	float cos = cosf(radians);

	m_data[0] = cos;
	m_data[1] = sin;
	m_data[2] = 0.0f;

	m_data[3] = -sin;
	m_data[4] = cos;
	m_data[5] = 0.0f;

	m_data[6] = 0.0f;
	m_data[7] = 0.0f;
	m_data[8] = 1.0f;
}

void Matrix3::rotation(Vector3& rot)
{
	Matrix3 matrixRot1;
	Matrix3 matrixRot2;
	
	matrixRot1.rotationZ(rot.z);
	matrixRot2.rotationX(rot.x);
	matrixRot1 *= matrixRot2;
	matrixRot2.rotationY(rot.y);
	matrixRot1 *= matrixRot2;
	*this = matrixRot1;
}

void Matrix3::rotationZYX(Vector3& rot)
{
	Matrix3 matrixRot1;
	Matrix3 matrixRot2;
	
	matrixRot1.rotationZ(rot.z);
	matrixRot2.rotationY(rot.y);
	matrixRot1 *= matrixRot2;
	matrixRot2.rotationX(rot.x);
	matrixRot1 *= matrixRot2;
	*this = matrixRot1;
}

void Matrix3::rotationEuler(Vector3& axis, float angle)
{
	float s = sinf(angle);
	float c = cosf(angle);
	float t = 1 - c;

	m_data[0] = t*axis.x*axis.x + c;
	m_data[1] = t*axis.x*axis.y + s*axis.z;
	m_data[2] = t*axis.x*axis.z - s*axis.y;

	m_data[3] = t*axis.x*axis.y - s*axis.z;
	m_data[4] = t*axis.y*axis.y + c;
	m_data[5] = t*axis.y*axis.z + s*axis.x;

	m_data[6] = t*axis.x*axis.y + s*axis.y;
	m_data[7] = t*axis.y*axis.z - s*axis.x;
	m_data[8] = t*axis.z*axis.z + c;
}

void Matrix3::orthonormalize()
{
	// This method is taken from the Wild Magic library v3.11, available at
	// http://www.geometrictools.com.

    // Algorithm uses Gram-Schmidt orthogonalization.  If 'this' matrix is
    // M = [m0|m1|m2], then orthonormal output matrix is Q = [q0|q1|q2],
    //
    //   q0 = m0/|m0|
    //   q1 = (m1-(q0*m1)q0)/|m1-(q0*m1)q0|
    //   q2 = (m2-(q0*m2)q0-(q1*m2)q1)/|m2-(q0*m2)q0-(q1*m2)q1|
    //
    // where |V| indicates length of vector V and A*B indicates dot
    // product of vectors A and B.

	//(1.0/sqrt((double)fValue))

    // compute q0
    float invLength = static_cast<float>(1.0/sqrt((double)(m_data[0]*m_data[0] +
        m_data[3]*m_data[3] + m_data[6]*m_data[6])));

    m_data[0] *= invLength;
    m_data[3] *= invLength;
    m_data[6] *= invLength;

    // compute q1
    float dot0 = m_data[0]*m_data[1] + m_data[3]*m_data[4] +
        m_data[6]*m_data[7];

    m_data[1] -= dot0*m_data[0];
    m_data[4] -= dot0*m_data[3];
    m_data[7] -= dot0*m_data[6];

    invLength = static_cast<float>(1.0/sqrt((double)(m_data[1]*m_data[1] +
        m_data[4]*m_data[4] + m_data[7]*m_data[7])));

    m_data[1] *= invLength;
    m_data[4] *= invLength;
    m_data[7] *= invLength;

    // compute q2
    float dot1 = m_data[1]*m_data[2] + m_data[4]*m_data[5] +
        m_data[7]*m_data[8];

    dot0 = m_data[0]*m_data[2] + m_data[3]*m_data[5] +
        m_data[6]*m_data[8];

    m_data[2] -= dot0*m_data[0] + dot1*m_data[1];
    m_data[5] -= dot0*m_data[3] + dot1*m_data[4];
    m_data[8] -= dot0*m_data[6] + dot1*m_data[7];

    invLength = static_cast<float>(1.0/sqrt((double)(m_data[2]*m_data[2] +
        m_data[5]*m_data[5] + m_data[8]*m_data[8])));

    m_data[2] *= invLength;
    m_data[5] *= invLength;
    m_data[8] *= invLength;
}

float Matrix3::operator[] (uint32 pos) const
{
    return m_data[pos];
}

float& Matrix3::operator[] (uint32 pos)
{
    return m_data[pos];
}

float Matrix3::operator() (uint32 row, uint32 col) const
{
    return m_data[index(row,col)];
}

float& Matrix3::operator() (uint32 row, uint32 col)
{
    return m_data[index(row,col)];
}

bool Matrix3::operator== (const Matrix3& matrix) const
{
    return (memcmp(m_data, matrix.m_data, 9*sizeof(float)) == 0);
}

bool Matrix3::operator!= (const Matrix3& matrix) const
{
    return (memcmp(m_data, matrix.m_data, 9*sizeof(float)) != 0);
}

Matrix3 Matrix3::operator* (const Matrix3& matrix) const
{
	Matrix3 prod;

	for (uint32 row = 0; row < 3; row++) 
	{
		for (uint32 col = 0; col < 3; col++)
		{
			uint32 i = index(row, col);
			prod.m_data[i] = 0.0f;
			for (uint32 mid = 0; mid < 3; mid++)
			{
				prod.m_data[i] += m_data[index(row, mid)] * matrix.m_data[index(mid, col)];
			}
		}
	}
	return prod;
}

Matrix3 Matrix3::operator+ (const Matrix3& matrix) const
{
	Matrix3 sum;

	for ( uint32 i = 0; i < 3*3; i++ )
		sum.m_data[i] = m_data[i] + matrix.m_data[i];

	return sum;
}

Matrix3 Matrix3::operator- (const Matrix3& matrix) const
{
	Matrix3 diff;

	for ( uint32 i = 0; i < 3*3; i++ )
		diff.m_data[i] = m_data[i] - matrix.m_data[i];

	return diff;
}

Matrix3 Matrix3::operator* (float scalar) const
{
	Matrix3 prod;

	for (uint32 i = 0; i < 3*3; i++)
		prod.m_data[i] = m_data[i] * scalar;

	return prod;
}

Matrix3 Matrix3::operator/ (float scalar) const
{
	Matrix3 quot;
	if ( scalar != 0.0f )
	{
		float invScalar = 1.0f / scalar;
		for ( uint32 i = 0; i < 3*3; i++ )
			quot.m_data[i] = m_data[i] * invScalar;
	}
	else
	{
		for ( uint32 i = 0; i < 3*3; i++ )
			quot.m_data[i] = 0;
	}

	return quot;
}

Matrix3 Matrix3::operator- () const
{
	Matrix3 neg;

	for ( uint32 i = 0; i < 3*3; i++ )
		neg.m_data[i] = -m_data[i];

	return( neg );
}

Matrix3& Matrix3::operator+= (const Matrix3& matrix)
{
	for ( uint32 i = 0; i < 3*3; i++ )
		m_data[i] += matrix.m_data[i];

	return *this;
}

Matrix3& Matrix3::operator-= (const Matrix3& matrix)
{
	for ( uint32 i = 0; i < 3*3; i++ )
		m_data[i] -= matrix.m_data[i];

	return *this;
}

Matrix3& Matrix3::operator*= (float scalar)
{
	for ( uint32 i = 0; i < 3*3; i++ )
		m_data[i] *= scalar;

	return *this;
}

Matrix3& Matrix3::operator*= (const Matrix3& matrix)
{
	Matrix3 prod = *this; 
	
	for ( uint32 row = 0; row < 3; row++ )
	{
		for ( uint32 col = 0; col < 3; col++ )
		{
			uint32 i = index( row, col );
			m_data[i] = 0.0f;
			for ( uint32 mid = 0; mid < 3; mid++ )
			{
				m_data[i] += prod.m_data[index(row, mid)] * matrix.m_data[index(mid, col)];
			}
		}
	}
	return *this;
}

Matrix3& Matrix3::operator/= (float scalar)
{
	if ( scalar != 0.0f )
	{
		float invScalar = 1.0f / scalar;	
		for ( uint32 i = 0; i < 3*3; i++ )
			m_data[i] *= invScalar;
	}
	else
	{
		for ( uint32 i = 0; i < 3*3; i++ )
			m_data[i] = 0;
	}

	return *this;
}

void Matrix3::setZero()
{
	memset(m_data, 0, 3*3*sizeof(float));
}

void Matrix3::setIdentity()
{
	for (uint32 row = 0; row < 3; row++)
	{
		for (uint32 col = 0; col < 3; col++)
		{
			if (row == col)
                m_data[index(row,col)] = 1.0f;
			else
				m_data[index(row,col)] = 0.0f;
		}
	}
}

void Matrix3::setTranspose()
{
	Matrix3 transpose;

	for ( uint32 row = 0; row < 3; row++ )
	{
		for ( uint32 col = 0; col < 3; col++ )
			transpose.m_data[index(row,col)] = m_data[index(col,row)];
	}
    
	memcpy(m_data, transpose.m_data, 3*3*sizeof(float));
}

Matrix3 Matrix3::zero()
{
	return Matrix3(true);
}

Matrix3 Matrix3::identity()
{
    return Matrix3(1.0f, 0.0f, 0.0f,
                   0.0f, 1.0f, 0.0f,
                   0.0f, 0.0f, 1.0f);
}

Matrix3 Matrix3::transpose()
{
	Matrix3 transpose;

	for ( uint32 row = 0; row < 3; row++ )
	{
		for ( uint32 col = 0; col < 3; col++ )
			transpose.m_data[index(row,col)] = m_data[index(col,row)];
	}
	return transpose;
}

uint32 Matrix3::index( uint32 row, uint32 col )
{
    return (3*row + col);
}

Vector3 Matrix3::operator* (const Vector3& vector) const
{
    Vector3 vectProd;
    for (uint32 col = 0; col < 3; col++)
    {
        vectProd[col] = 0.0f;
        for (uint32 row = 0; row < 3; row++)
            vectProd[col] += m_data[index(row,col)] * vector[row];
    }
    return vectProd;
}

void Matrix3::setRow(uint32 row, const Vector3& vector)
{
	for ( uint32 col = 0; col < 3; col++ )
        m_data[index(row,col)] = vector[col];
}

Vector3 Matrix3::getRow(uint32 row) const
{
	Vector3 vRow;
	for ( uint32 col = 0; col < 3; col++ )
        vRow[col] = m_data[index(row,col)];

	return vRow;
}

void Matrix3::setColumn(uint32 col, const Vector3& vector)
{
	for ( uint32 row = 0; row < 3; row++ )
        m_data[index(row,col)] = vector[row];
}

Vector3 Matrix3::getColumn(uint32 col) const
{
	Vector3 vCol;
	for ( uint32 row = 0; row < 3; row++ )
		vCol[row] = m_data[index(row,col)];

	return vCol;
}

OC_NS_END;
