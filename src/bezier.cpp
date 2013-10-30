#include "bezier.h"

int bezier::nCi(int n, int i)
{
	if(i == 0 || i == n)
		return 1;
	else if(i == 1 || i == n -1)
		return n;
	else
		{	
			if(choose[n][i] != 0)
				return choose[n][i];
			else
				choose[n][i] = nCi(n-1,i-1) + nCi(n-1,i);
				return choose[n][i];
		}
}

bezier::bezier()
{
	for(int i = 0;i < 100; i++)
	{
		for(int j = 0;j < 100; j++)
		{
			this->choose[i][j] = 0;
		}
	}
	l = 0;
}
void bezier::addCP(double a, double b, double c)
{
	pnt* np = new pnt(a, b, c);
	c_pnts.push_back(*np);
	l = l + 1;
}

void bezier::del_lastCP()
{
	pnt* np;

	np = &c_pnts[c_pnts.size() - 1];
	c_pnts.pop_back();
	l = l - 1;
}

pnt bezier::value(double k)
{
	double a = 0,b = 0,c = 0;
	int n = l -1;
	if(k == 0)
	{
		a = c_pnts[0].x;
		b = c_pnts[0].y;
		c = c_pnts[0].z;
	}
	else if(k > 0.99)
	{
		a = c_pnts[l-1].x;
		b = c_pnts[l-1].y;
		c = c_pnts[l-1].z;	
	}
	else
	{
		for(int j = 0; j <= n; j++)
		{
			a = a + (c_pnts[j].x)*nCi(n,j)*pow(k,j)*pow(1.0-k,n-j);
			b = b + (c_pnts[j].y)*nCi(n,j)*pow(k,j)*pow(1.0-k,n-j);
			c = c + (c_pnts[j].z)*nCi(n,j)*pow(k,j)*pow(1.0-k,n-j); 
		}		
	}
	pnt* np = new pnt(a, b, c);
	return *np;

}
void bezier::draw(int n)
{
	float x = (1.0/((double)n)),k;
	glLineWidth(4);
	glBegin(GL_LINE_STRIP);
	for(k = 0;k <= 1.001;k = k + x)
	{
		glVertex3f(value(k).x,value(k).y,value(k).z);
		//std::cout<<"drawn at :"<<value(k).x<<" "<<value(k).y<<" "<<value(k).z<<"\n";	
	}
	glEnd();
}

void bezier::drawcp()
{
	int i;
	for(i = 0;i < l;i++)
	{
		glPushMatrix();
			glTranslatef(c_pnts[i].x,c_pnts[i].y,c_pnts[i].z);
			glScalef(1,1,1);
			drawBox(0.01,GL_QUADS);
		glPopMatrix();
	}
}