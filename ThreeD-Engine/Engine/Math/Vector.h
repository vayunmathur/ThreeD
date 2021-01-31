#pragma once
#include <memory>


class vec3 {
public:
	vec3() : x(0), y(0), z(0) {}
	vec3(float x, float y, float z) : x(x), y(y), z(z) {}
	vec3(const vec3& vector) : x(vector.x), y(vector.y), z(vector.z) {}

	static vec3 lerp(const vec3& start, const vec3& end, float delta) {
		vec3 v;
		v.x = start.x * (1.0f - delta) + end.x * delta;
		v.y = start.y * (1.0f - delta) + end.y * delta;
		v.z = start.z * (1.0f - delta) + end.z * delta;
		return v;
	}

	~vec3() {

	}
public:
	float x, y, z;
};


class mat4 {
public:
	mat4() {}

	void setIdentity()
	{
		::memset(m_mat, 0, sizeof(float) * 16);
		m_mat[0][0] = 1;
		m_mat[1][1] = 1;
		m_mat[2][2] = 1;
		m_mat[3][3] = 1;
	}

	void setTranslation(const vec3& translation)
	{
		setIdentity();
		m_mat[3][0] = translation.x;
		m_mat[3][1] = translation.y;
		m_mat[3][2] = translation.z;
	}

	void setScale(const vec3& scale) {
		setIdentity();
		m_mat[0][0] = scale.x;
		m_mat[1][1] = scale.y;
		m_mat[2][2] = scale.z;
	}

	void setRotationX(float x)
	{
		m_mat[1][1] = cos(x);
		m_mat[1][2] = sin(x);
		m_mat[2][1] = -sin(x);
		m_mat[2][2] = cos(x);
	}

	void setRotationY(float y)
	{
		m_mat[0][0] = cos(y);
		m_mat[0][2] = -sin(y);
		m_mat[2][0] = sin(y);
		m_mat[2][2] = cos(y);
	}

	void setRotationZ(float z)
	{
		m_mat[0][0] = cos(z);
		m_mat[0][1] = sin(z);
		m_mat[1][0] = -sin(z);
		m_mat[1][1] = cos(z);

	}

	mat4& operator *=(const mat4& matrix) {
		mat4 out;
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				out.m_mat[i][j] =
					m_mat[i][0] * matrix.m_mat[0][j]
					+ m_mat[i][1] * matrix.m_mat[1][j]
					+ m_mat[i][2] * matrix.m_mat[2][j]
					+ m_mat[i][3] * matrix.m_mat[3][j];
			}
		}
		::memcpy(m_mat, out.m_mat, sizeof(float) * 16);
		return *this;
	}

	void setOrthoLH(float width, float height, float near_plane, float far_plane)
	{
		setIdentity();
		m_mat[0][0] = 2.0f / width;
		m_mat[1][1] = 2.0f / height;
		m_mat[2][2] = 1.0f / (far_plane - near_plane);
		m_mat[3][2] = -(near_plane / (far_plane - near_plane));
	}

	~mat4() {

	}
private:
	float m_mat[4][4];
};