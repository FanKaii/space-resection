#ifndef SPACE_RESECTION_H_
#define SPACE_RESECTION_H_

#include <opencv.hpp>
#include <fstream>
#include <vector>

class SpaceResection
{
public:
	/*
	* elems include {fx,fy,x0,y0,k1,k2,p1,p2,width,height,X,Y,Z,phi,omega,kappa} phi,omega,kappa�ԽǶ�Ϊ��λ
	*/
	SpaceResection &setInitialValue(const std::vector<double> &elems);     

	//�������Ϊ��ͼ������Ϊԭ�㣬y�����ϣ�x�����ҵ�����ϵ�µ����꣨����Ļ���꣩
	//�ļ�����3��n�У�ÿһ�е�һ��Ϊ���id,�ڶ���Ϊx���꣬������Ϊy����
	bool importImagePoints(const std::string &file);

	//�ļ�����4��n�У�ÿһ�е�һ��Ϊ���id,�ڶ���ΪX���꣬������ΪY����,������ΪZ����
	bool importControlPoints(const std::string &file);

	/*
	*  {fx,fy,x0,y0,k1,k2,p1,p2,X,Y,Z,phi,omega,kappa}
	*/
	const std::vector<double> &slove(const std::string &file);

private:
	class Point2D
	{
	public:
		Point2D() = default;
		Point2D(size_t idex, float x, float y) :idex(idex), x(x), y(y) {}

		float x, y;
		size_t idex;
	};

	class Point3D
	{
	public:
		Point3D() = default;
		Point3D(size_t idex, double X, double Y, double Z) :idex(idex), m_X(X), m_Y(Y), m_Z(Z) {}

		size_t idex;

		double getX()const { return m_X; }
		double getY()const { return m_Y; }
		double getZ()const { return m_Z; }
	private:
		double m_X = 0;
		double m_Y = 0;
		double m_Z = 0;
	};

	double m_fx, m_fy, m_x0, m_y0;                 
	double m_k1, m_k2, m_p1, m_p2;
	double m_X, m_Y, m_Z, m_phi, m_omega, m_kappa;
	int m_width, m_height;

	std::vector<double> m_corrected_elems;

	std::vector<Point2D> m_imagePoints;
	std::vector<Point3D> m_controlPoints;

	double angleToRadian(double angle)const { return angle / 180.0*CV_PI; }
	double radianToAngle(double radian)const { return radian / CV_PI*180.0; }

	void accuracyCompute(double &)const;
	void storage(double &, const std::string &)const;
};

#endif