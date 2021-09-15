#include "Mat4.h"


//Constructors
Mat4::Mat4() : mat(4, std::vector<double>(4)) {
	mat[0][0] = 1;
	mat[1][1] = 1;
	mat[2][2] = 1;
	mat[3][3] = 1;
};
Mat4::Mat4(double number) : mat(4, std::vector<double>(4, number)) {};
Mat4::Mat4(double m00, double m01, double m02, double m03,
	double m10, double m11, double m12, double m13,
	double m20, double m21, double m22, double m23,
	double m30, double m31, double m32, double m33)
	: mat(4, std::vector<double>(4)) {
	mat[0][0] = m00; mat[0][1] = m01; mat[0][2] = m02; mat[0][3] = m03;
	mat[1][0] = m10; mat[1][1] = m11; mat[1][2] = m12; mat[1][3] = m13;
	mat[2][0] = m20; mat[2][1] = m21; mat[2][2] = m22; mat[2][3] = m23;
	mat[3][0] = m30; mat[3][1] = m31; mat[3][2] = m32; mat[3][3] = m33;
}
Mat4::Mat4(std::vector<std::vector<double>> a) : mat(a){}

//Useful functions
const std::vector<std::vector<double>>& Mat4::getmat() const {
	return mat;
}

Mat4 Mat4::transpose() const {
	Mat4 trans = Mat4();
	for (int i = 0; i < 4; i++){
		for(int j = 0; j < 4; j++){
			trans(j, i) = (*this)(i, j);
		}
	}
	return trans;
}

Mat4 Mat4::inverse() const{

	auto temp = std::vector<std::vector<double>>(4, std::vector<double>(4));
	auto findSubMatrix = [](std::vector<std::vector<double>> a, int row, int col) {

		std::vector <std::vector<double>> subMat = std::vector <std::vector<double>>(a.size() - 1, std::vector<double>(a.size() - 1));
		int curRow = 0;
		int curCol = 0;

		for (int i = 0; i < a.size(); i++) {
			for (int j = 0; j < a.size(); j++) {
				if (!(i == row || j == col)) {
					subMat[curRow][curCol] = a[i][j];
					curCol++;
				}
			}
			if (i != row) {
				curRow++;
			}
			curCol = 0;
		}
		return subMat;
	};
	

	auto findDeterminant = [&findSubMatrix](std::vector<std::vector<double>> a) {
		auto findDeterminant_ = [&findSubMatrix](std::vector<std::vector<double>> a, auto findDeterminant) {

			double total = 0;
			int sign = 1;
			if (a.size() == 2) {
				return(a[0][0] * a[1][1] - a[0][1] * a[1][0]);
			}
			for (int i = 0; i < a.size(); i++) {
				total += findDeterminant(findSubMatrix(a, 0, i), findDeterminant) * sign * a[0][i];
				sign *= -1;
			}
			return total;
		};
		return findDeterminant_(a, findDeterminant_);

	};

	auto findCofactors = [&findSubMatrix, &findDeterminant, &temp](std::vector<std::vector<double>> a, std::vector<std::vector<double>> temp) {
		auto findCofactors_ = [&findSubMatrix, &findDeterminant, &temp](std::vector<std::vector<double>> a, auto findCofactors_) {
			int sign = 1;
			for (int i = 0; i < a.size(); i++) {
				for (int j = 0; j < a.size(); j++){
					temp[i][j] = findDeterminant(findSubMatrix(a, i, j)) * sign;
				}
			}
			return temp;
		};
		return findCofactors_(a, findCofactors_);
	};

	auto det = findDeterminant(this->getmat());
	assert(det != 0);
	auto cofactors = findCofactors(this->getmat(), temp);
	int sign = 1;
	for (int i = 0; i < cofactors.size(); i++) {
		for (int j = 0; j < cofactors.size(); j++) {
			cofactors[i][j] *= sign;
			sign *= -1;
		}
		sign *= -1;
	}
	Mat4 toReturn = Mat4(cofactors).transpose();
	toReturn = toReturn/det;

	return toReturn;

}


//operators
double& Mat4::operator()(int row, int col) {
	return Mat4::mat[row][col];
}

const double Mat4::operator()(int row, int col) const {
	return Mat4::mat[row][col];
}

Mat4 Mat4::operator+(const Mat4& a) {
	return Mat4((*this)(0,0) + a(0, 0), (*this)(0, 1) + a(0, 1), (*this)(0, 2) + a(0, 2), (*this)(0, 3) + a(0, 3)
	, (*this)(1, 0) + a(1, 0), (*this)(1, 1) + a(1, 1), (*this)(1, 2) + a(1, 2), (*this)(1, 3) + a(1, 3)
	, (*this)(2, 0) + a(2, 0), (*this)(2, 1) + a(2, 1), (*this)(2, 2) + a(2, 2), (*this)(2, 3) + a(2, 3)
	, (*this)(3, 0) + a(3, 0), (*this)(3, 1) + a(3, 1), (*this)(3, 2) + a(3, 2), (*this)(3, 3) + a(3, 3));
}

const Mat4 Mat4::operator+(const Mat4& a) const {
	return Mat4((*this)(0, 0) + a(0, 0), (*this)(0, 1) + a(0, 1), (*this)(0, 2) + a(0, 2), (*this)(0, 3) + a(0, 3)
		, (*this)(1, 0) + a(1, 0), (*this)(1, 1) + a(1, 1), (*this)(1, 2) + a(1, 2), (*this)(1, 3) + a(1, 3)
		, (*this)(2, 0) + a(2, 0), (*this)(2, 1) + a(2, 1), (*this)(2, 2) + a(2, 2), (*this)(2, 3) + a(2, 3)
		, (*this)(3, 0) + a(3, 0), (*this)(3, 1) + a(3, 1), (*this)(3, 2) + a(3, 2), (*this)(3, 3) + a(3, 3));
}


Mat4 Mat4::operator-(const Mat4& a) {
	return Mat4((*this)(0, 0) - a(0, 0), (*this)(0, 1) - a(0, 1), (*this)(0, 2) - a(0, 2), (*this)(0, 3) - a(0, 3)
		, (*this)(1, 0) - a(1, 0), (*this)(1, 1) - a(1, 1), (*this)(1, 2) - a(1, 2), (*this)(1, 3) - a(1, 3)
		, (*this)(2, 0) - a(2, 0), (*this)(2, 1) - a(2, 1), (*this)(2, 2) - a(2, 2), (*this)(2, 3) - a(2, 3)
		, (*this)(3, 0) - a(3, 0), (*this)(3, 1) - a(3, 1), (*this)(3, 2) - a(3, 2), (*this)(3, 3) - a(3, 3));
}

const Mat4 Mat4::operator-(const Mat4& a) const {
	return Mat4((*this)(0, 0) - a(0, 0), (*this)(0, 1) - a(0, 1), (*this)(0, 2) - a(0, 2), (*this)(0, 3) - a(0, 3)
		, (*this)(1, 0) - a(1, 0), (*this)(1, 1) - a(1, 1), (*this)(1, 2) - a(1, 2), (*this)(1, 3) - a(1, 3)
		, (*this)(2, 0) - a(2, 0), (*this)(2, 1) - a(2, 1), (*this)(2, 2) - a(2, 2), (*this)(2, 3) - a(2, 3)
		, (*this)(3, 0) - a(3, 0), (*this)(3, 1) - a(3, 1), (*this)(3, 2) - a(3, 2), (*this)(3, 3) - a(3, 3));
}

bool Mat4::operator==(const Mat4& a) {

	if (a.mat == (*this).mat) {
		return true;
	}
	return false;
}

const bool Mat4::operator==(const Mat4& a) const {
	if (a.mat == (*this).mat) {
		return true;
	}
	return false;
}

Mat4 Mat4::operator*(const Mat4& a) {
	Mat4 toReturn = Mat4();
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			toReturn(i, j) = (*this)(i, 0) * a(0, j) +
				(*this)(i, 1) * a(1, j) +
				(*this)(i, 2) * a(2, j) +
				(*this)(i, 3) * a(3, j);
		}
	}
	return toReturn;
}

const Mat4 Mat4::operator*(const Mat4& a) const {
	Mat4 toReturn = Mat4();
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			toReturn(i, j) = (*this)(i, 0) * a(0, j) +
				(*this)(i, 1) * a(1, j) +
				(*this)(i, 2) * a(2, j) +
				(*this)(i, 3) * a(3, j);
		}
	}
	return toReturn;
}

vec3 Mat4::operator*(const vec3& a) {
	
	return vec3((*this)(0, 0) * a.getx() + (*this)(0, 1) * a.gety() + (*this)(0, 2) * a.getz(),
		(*this)(1, 0) * a.getx() + (*this)(1, 1) * a.gety() + (*this)(1, 2) * a.getz(),
		(*this)(2, 0) * a.getx() + (*this)(2, 1) * a.gety() + (*this)(2, 2) * a.getz());

}

const vec3 Mat4::operator*(const vec3& a) const {

	return vec3((*this)(0, 0) * a.getx() + (*this)(0, 1) * a.gety() + (*this)(0, 2) * a.getz(),
		(*this)(1, 0) * a.getx() + (*this)(1, 1) * a.gety() + (*this)(1, 2) * a.getz(),
		(*this)(2, 0) * a.getx() + (*this)(2, 1) * a.gety() + (*this)(2, 2) * a.getz());

}

 point3 Mat4::operator*(const point3& a)  {

	double x = (*this)(0, 0) * a.getx() + (*this)(0, 1) * a.gety() + (*this)(0, 2) * a.getz() + (*this)(0,3);
	double y = (*this)(1, 0) * a.getx() + (*this)(1, 1) * a.gety() + (*this)(1, 2) * a.getz() + (*this)(1, 3);
	double z = (*this)(2, 0) * a.getx() + (*this)(2, 1) * a.gety() + (*this)(2, 2) * a.getz() + (*this)(2, 3);
	double w = (*this)(3, 0) * a.getx() + (*this)(3, 1) * a.gety() + (*this)(3, 2) * a.getz() + (*this)(3, 3);

	return point3(x / w, y / w, z / w);
}

 const point3 Mat4::operator*(const point3& a) const {

	 double x = (*this)(0, 0) * a.getx() + (*this)(0, 1) * a.gety() + (*this)(0, 2) * a.getz() + (*this)(0, 3);
	 double y = (*this)(1, 0) * a.getx() + (*this)(1, 1) * a.gety() + (*this)(1, 2) * a.getz() + (*this)(1, 3);
	 double z = (*this)(2, 0) * a.getx() + (*this)(2, 1) * a.gety() + (*this)(2, 2) * a.getz() + (*this)(2, 3);
	 double w = (*this)(3, 0) * a.getx() + (*this)(3, 1) * a.gety() + (*this)(3, 2) * a.getz() + (*this)(3, 3);

	 return point3(x / w, y / w, z / w);
 }

 ray Mat4::operator*(const ray& a) {
	 return ray((*this) * a.getOrigin(), (*this) * a.getDirection());
 }

 const ray Mat4::operator*(const ray& a) const {
	 return ray((*this) * a.getOrigin(), (*this) * a.getDirection());
 }

 Mat4 Mat4::operator*(const double a) {
	 return Mat4((*this)(0, 0) * a, (*this)(0, 1) * a, (*this)(0, 2) * a, (*this)(0, 3) * a
		 , (*this)(1, 0) * a, (*this)(1, 1) * a, (*this)(1, 2) * a, (*this)(1, 3) * a
		 , (*this)(2, 0) * a, (*this)(2, 1) * a, (*this)(2, 2) * a, (*this)(2, 3) * a
		 , (*this)(3, 0) * a, (*this)(3, 1) * a, (*this)(3, 2) * a, (*this)(3, 3) * a);
 }

 const Mat4 Mat4::operator*(const double a) const {
	 return Mat4((*this)(0, 0) * a, (*this)(0, 1) * a, (*this)(0, 2) * a, (*this)(0, 3) * a
		 , (*this)(1, 0) * a, (*this)(1, 1) * a, (*this)(1, 2) * a, (*this)(1, 3) * a
		 , (*this)(2, 0) * a, (*this)(2, 1) * a, (*this)(2, 2) * a, (*this)(2, 3) * a
		 , (*this)(3, 0) * a, (*this)(3, 1) * a, (*this)(3, 2) * a, (*this)(3, 3) * a);
 }

 Mat4 Mat4::operator/(const double a) {
	 return Mat4((*this)(0, 0) / a, (*this)(0, 1) / a, (*this)(0, 2) / a, (*this)(0, 3) / a
		 , (*this)(1, 0) / a, (*this)(1, 1) / a, (*this)(1, 2) / a, (*this)(1, 3) / a
		 , (*this)(2, 0) / a, (*this)(2, 1) / a, (*this)(2, 2) / a, (*this)(2, 3) / a
		 , (*this)(3, 0) / a, (*this)(3, 1) / a, (*this)(3, 2) / a, (*this)(3, 3) / a);
 }


 const Mat4 Mat4::operator/(const double a) const {
	 return Mat4((*this)(0, 0) / a, (*this)(0, 1) / a, (*this)(0, 2) / a, (*this)(0, 3) / a
		 , (*this)(1, 0) / a, (*this)(1, 1) / a, (*this)(1, 2) / a, (*this)(1, 3) / a
		 , (*this)(2, 0) / a, (*this)(2, 1) / a, (*this)(2, 2) / a, (*this)(2, 3) / a
		 , (*this)(3, 0) / a, (*this)(3, 1) / a, (*this)(3, 2) / a, (*this)(3, 3) / a);
 }