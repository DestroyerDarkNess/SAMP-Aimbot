#include "stdafx.h"
#include <windows.h>
#include <math.h>

int AimToggle = 0;

void gta_showText(PCHAR text, UINT time, USHORT flag, bool bPreviousBrief)
{
    ((void(__cdecl *)(PCHAR, UINT, USHORT, bool))0x69F1E0)(text, time, flag, bPreviousBrief);
}

void AimbotOn()
{
   DWORD* pTarget = (DWORD*)0xB6F3B8;//pointer of target object.
   DWORD* pActor = (DWORD*)0xB6F5F0;//pointer of player actor
   DWORD* pCamera = (DWORD*)0xB6F99C;//camera pointer
   float* camXpos = (float*)0xB6F258;//writeable camera Z angle
   // No Spread
			for (int addr = 0xC8C450; addr < 0xC8C8B0; addr += 0x70)
                *(DWORD *)addr = 0x40000000;
			 // Aimbot
          if(*pActor > 0)  {
					

         char* pVehicle = (char*)((*pActor) + 0x46C);
         if(*pVehicle != 1)
         {
             DWORD* pMtrx1 = (DWORD*)((*pActor) + 0x14);//matrix of player actor
             float* xPos1 = (float*)((*pMtrx1) + 0x30);//player actor X position
             float* yPos1 = (float*)((*pMtrx1) + 0x34);//player actor Y position

             float* CxPos1 = (float*)(0xB6F9CC);//camera X position
             float* CyPos1 = (float*)(0xB6F9D0);//camera Y position
 
             float xPoint = *CxPos1;
             float yPoint = *CyPos1;
 
             int* keyt = (int*)0xB7347A;//Left mouse key
             DWORD* pPed = (DWORD*) ((*pTarget) + 0x79C);//pointer to target player
   
            if(*pPed > 0) {
           
                  float* playerSpeedVectorX = (float*)((*pPed) + 0x44);// Player speed angle vector.
                  float* playerSpeedVectorY = (float*)((*pPed) + 0x48);

                  DWORD* pMtrx2 = (DWORD*)((*pPed) + 0x14);//matrix of target player
                  float* xPos2 = (float*)((*pMtrx2) + 0x30);//X position
                  float* yPos2 = (float*)((*pMtrx2) + 0x34);//Y position
   
                   float xPos2a;
                   float yPos2a;
 
                   float* playerHP = (float*)((*pPed) + 0x540);//health of target player
                   if(*playerHP > 0){
         
                      xPos2a = *xPos2+ *playerSpeedVectorX*6;//position not far from target player sceen
                      yPos2a = *yPos2+ *playerSpeedVectorY*6;
       
                      float Aa = fabs(xPoint-xPos2a);
                      float Ab = fabs(yPoint-yPos2a);
                      float Ac = sqrt(Aa*Aa+Ab*Ab);
                      float alpha = asin(Aa/Ac);
                      float beta = acos(Aa/Ac);
                     if((*xPos1 > *xPos2)&&(*yPos1 < *yPos2)){beta = -beta;}//1 part
                     if((*xPos1 > *xPos2)&&(*yPos1 > *yPos2)){beta = beta;}//2 part
                     if((*xPos1 < *xPos2)&&(*yPos1 > *yPos2)){beta = (alpha + (1.5707));}//3 part
                     if((*xPos1 < *xPos2)&&(*yPos1 < *yPos2)){beta = (-alpha - (1.5707));}//4 part
         
                     if(*keyt > 0){
                         *camXpos = beta+0.0389;//for deagle.
                     }
                }
             }
        }
    }
}

void AimbotOFF()
{
	 // No Spread OFF
			for (int addr = 0xC8C450; addr < 0xC8C8B0; addr += 0x70)
                *(DWORD *)addr = 0x3F800000;
     Sleep(10);
// ExitThread(0);
}


void main()
{
   while(1)
  {
	  if (GetAsyncKeyState(VK_NUMPAD0) & 0x8000)
        {
            Sleep(200);
            AimToggle = !AimToggle;

			 if (AimToggle) {
                 gta_showText("[ugbase.eu]~g~Aimbot Activated!!", 2000, NULL, NULL);
				
            }
            else {
            	gta_showText("[ugbase.eu]~r~Aimbot Deactivated!!", 2000, NULL, NULL);
			
			}
        }
				
		 if (AimToggle) {
                AimbotOn();
            }
            else {
            	AimbotOFF();
          }
    }
   
}

  

BOOL APIENTRY DllMain(HINSTANCE hDll, DWORD callReason, LPVOID lpReserved)
{
if(callReason == DLL_PROCESS_ATTACH)
{
CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)&main, 0, 0, 0);
}
return 1;
}
