struct IMG
{
      byte* bytes; //массив данных
      int Width; //ширина в пикселях
      int Width_1; //ширина в байтах
      int Height; //высота
      bool on; //загружено изображение или нет
      BYTE format;//0 – 24бит 1 – 8 бит чёрнобелое
};

void AllocationBorders(IMG img)
{
      int i,j,k;
      for(i=0;i<img.Height;i++){
            for(j=0;j<img.Width;j++)
            {
                  if (img.bytes[j*3+i*img.Width_1]==255) 
                  	continue;
                  	k=0;
                  
                  	if (i!=0)
                        if (img.bytes[j*3+(i-1)*img.Width_1]==255) 
                        	k=1;
	      			if (i!=img.Height-1)
	            		if (img.bytes[j*3+(i+1)*img.Width_1]==255) 
	            			k=1;
  					if (j!=0)
        				if (img.bytes[(j-1)*3+i*img.Width_1]==255) 
        					k=1;
					if (j!=img.Width-1)
						if (img.bytes[(j+1)*3+i*img.Width_1]==255) 
							k=1;
		            if (k==1) 
                  	{
                        img.bytes[j*3+i*img.Width_1]=128;
                        img.bytes[j*3+i*img.Width_1+1]=0;
                        img.bytes[j*3+i*img.Width_1+2]=0;
                  	}

            }
      }  
}