#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>

#define FFMPEG "/usr/bin/ffmpeg"
using namespace std;


class cfxs
{
    public:
	FILE * buffer;
	char names[300][90], *cwd;
	char nsxt[300][90];
	char nsxte[300][90];
	int ilm;
	void printarr(char array [][90])
	{
	    int j,p;
	    for (j=0;j<ilm;j++)
		cout<<"IND:: "<<array[j]<<endl; 
	    /*for(j=0;j<ilm;j++)
	    {
		for(p=0;p<30;p++)
		    printf("0x%x ",array[j][p]);
		cout<<endl;
	    }*/
	}
	void safearray(char arr [][90], int id,int h)
	{
	    char ch;
	    int k=0;
	    while (ch != EOF)
	    {
		ch=fgetc(buffer);
		if (id <= 0)
		{
		    if (ch == 0xa)
		    {
		    	ilm++;
		    	k=0;
		    }
		    else
		    {
			if(ch >= 0x20 && ch<=0x7a)
			{
		    	    arr[ilm][k]=ch;
		    	    k++;
			}
		    }
	    	}
		else
		{
		    if(ch >= 0x20 && ch<=0x7a)
		    {
		    	arr[h][k]=ch;
		    	k++;
		    }
		}
	    }
	}
	void readbff()
	{
	    char lscommand[90],ch;
	    ilm=0;
	    cwd=(char *) malloc(800*sizeof(char));
	    sprintf(lscommand,"ls ");
	    cwd=getcwd(cwd,800*sizeof(cwd));
	    strcat(lscommand,cwd);
	    buffer=popen(lscommand,"r");
	    safearray(names,0,0);
	}
	void ubname()
	{
	    int j,ixt,k,l=0;
	    char *ccm,ch;
	    for(j=0;j<ilm;j++)
	    {
		ccm=strrchr(names[j],'.');
		if(ccm != NULL)
		{
		    //printf("PXX: 0x%x\n",ccm);
		    //printf("INDEX:: %d\n",ccm-names[j]); //for cut just last point '.' http://stackoverflow.com/questions/5309471/getting-file-extension-in-c
		    for(k=0;k<ccm-names[j];k++)
		    	nsxt[l][k]=names[j][k];
		    for(k=0;k<strlen(names[j]);k++)
		 	nsxte[l][k]=names[j][k];	
		    l++;
		}
	    }
	    ilm=l;
	    /*printarr(nsxt);
	    cout<<endl;
	    printarr(nsxte);*/
	}
	void convert(char fold[])
	{
	    char * ccm,*spath,*zpath;
	    int k;
	    ccm=(char *) malloc(800*sizeof(char));
	    spath=(char *) malloc(800*sizeof(char));
	    zpath=(char *) malloc(800*sizeof(char));
	    sprintf(spath,cwd);
	    strcat(spath,"/");
	    sprintf(zpath,spath);
	    strcat(spath,fold);
	    strcat(spath,"/");
	    cout<<spath<<endl;
	    cout<<zpath<<endl;
	    mkdir(spath,0777);
	    for(k=0;k<ilm;k++)
	    {
		sprintf(ccm,FFMPEG);
	    	strcat(ccm, " -i ");
		strcat(ccm,"\"");
		strcat(ccm,zpath);
		strcat(ccm,nsxte[k]);
		strcat(ccm,"\"");
		strcat(ccm," ");
		strcat(ccm,"\"");
		strcat(ccm,spath);
		strcat(ccm,nsxt[k]);
		strcat(ccm,".mp3");
		strcat(ccm,"\"");
		//cout<<"CMD:: "<<ccm<<endl;
		system(ccm);	
	    }
	}
};


int main(int argc, char * argv[])
{
    cfxs obj_cfx1;
    obj_cfx1.readbff();
    obj_cfx1.ubname();
    obj_cfx1.convert(argv[1]);
    return 0;
}

