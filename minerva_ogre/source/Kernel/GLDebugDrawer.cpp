#include <Kernel/GLDebugDrawer.h>

//#include <stdio.h> //printf debugging


GLDebugDrawer::GLDebugDrawer()
:m_debugMode(0)
{

}

void    GLDebugDrawer::drawLine(const btVector3& from,const btVector3& to,const btVector3& color)
{
   //      if (m_debugMode > 0)
  //std::cout<<"Drawing line!"<<std::endl;
   {
     //      float tmp[ 6 ] = { from.getX(), from.getY(), from.getZ(),
     //             to.getX(), to.getY(), to.getZ() };

     //Normal vectors are not painted!
     if(color.getX()==1 && color.getY()==1 && color.getZ()==0) return;
     glDisable(GL_LIGHTING);
     glDisable(GL_TEXTURE_2D);
     glMatrixMode(GL_MODELVIEW);
      glPushMatrix();

      //      std::cout<<"Color: x: "<<color.getX()<<", y: "<<color.getY()<<", z: "<<color.getZ()<<std::endl;
      glLineWidth(1.5);
      glColor3f(color.getX(),color.getY(),color.getZ());
      glBegin(GL_LINES);
      glVertex3f(from.getX(),from.getY(),from.getZ());
      glVertex3f(to.getX(),to.getY(),to.getZ());
      glEnd();
      glPopMatrix();
     glEnable(GL_LIGHTING);
   }
}

void    GLDebugDrawer::setDebugMode(int debugMode)
{
   m_debugMode = debugMode;
}


void    GLDebugDrawer::draw3dText(const btVector3& location,const char* textString)
{
   //glRasterPos3f(location.x(),  location.y(),  location.z());
   //BMF_DrawString(BMF_GetFont(BMF_kHelvetica10),textString);
}

void    GLDebugDrawer::reportErrorWarning(const char* warningString)
{
  Logger::getInstance()->error(warningString);
}

void    GLDebugDrawer::drawContactPoint(const btVector3& pointOnB,const btVector3& normalOnB,btScalar distance,int lifeTime,const btVector3& color)
{
   {
      //btVector3 to=pointOnB+normalOnB*distance;
      //const btVector3&from = pointOnB;
      //glColor4f(color.getX(), color.getY(), color.getZ(), 1.0f);

      //GLDebugDrawer::drawLine(from, to, color);

      //glRasterPos3f(from.x(),  from.y(),  from.z());
      //char buf[12];
      //sprintf(buf," %d",lifeTime);
      //BMF_DrawString(BMF_GetFont(BMF_kHelvetica10),buf);
   }
}
