#include "gunit.h"
#include "usart.h"//fputc

uint8_t is_same(void* a,void* b,uint8_t len)
{
  uint8_t i;
  uint8_t* A=(uint8_t*)a;
  uint8_t* B=(uint8_t*)b;

  printf("len=%02X\r\n",len);
  for(i=0;i<len;i++) printf("%02X ",A[i]);  printf("\r\n");
  for(i=0;i<len;i++) printf("%02X ",B[i]);  printf("\r\n");

  for(i=len-1;i!=0XFF;i--)
    if(A[i]!=B[i]) return 0;

  return 1;
}

/*万能打印 字符*/
void G_printCHR(void* A,uint8_t len)
{
	for(uint8_t i=0;i<len;i++)
		printf("%c",*( (unsigned char*)A+i   )    );
	printf("\r\n");
}


/*万能打印 HEX*/
void G_printHEX(void* A,uint16_t len)
{
  for(uint16_t i=0;i<len;i++)
		printf("%02X ",*( (unsigned char*)A+i   )    );  
  printf("\r\n");
}

void print_arr(char *name,unsigned char *arr,int len)
{
	printf("%s[%d]",name,len);
	if(len<10)
	{
	for(int a=0;a<len;a++)
		printf("%02X ",arr[a]);
	}
	printf("\r\n");	
}

 /*开机画面*/
void G_lovexin( void )
{
	float x,y,z,f;
	for(y=1.5f;y>-1.5f;y-=0.1f)
	{
		for(x=-1.5f;x<1.5f;x+=0.05f)
		{
			z=x*x+y*y-1;
			f=z*z*z-x*x*y*y*y;
			putchar( f<=0.0f ? ".:-=*#%@"[(int)(f*-8.0f)]:' ');
		}
		putchar('\r');
		putchar('\n');//和串口输出配合 此消彼长
	}
}

/*printf*/
int fputc(int ch, FILE *f)//FILE 需要头文件 #include <stdio.h> 放在main.h去吧
{
	uint8_t r='\r';
	if('\n'==ch)	HAL_UART_Transmit(&huart1 ,&r, 1 , 0xFFFF);
	HAL_UART_Transmit(&huart1 , (uint8_t *)&ch, 1 , 0xFFFF);
	return ch;
}

/*软件复位*/
void G_mcuReset(const char *funs)
{
    printf("function: %s,Line: %d,Time: %s\r\n", __FUNCTION__,__LINE__,__TIME__);
    HAL_NVIC_SystemReset();	
}

/*软件复位*/
void soft_system_resert( const char *funs )
{
    printf("System has been resert form %s\n" , funs);
    NVIC_SystemReset();
}


//完成'4'-->4  ‘A’-->10
unsigned char G_strTobyte(unsigned char dData)
{
	unsigned char rst=0;
	if((dData >= '0')&& (dData <= '9'))
				rst = dData-'0';
	else if((dData >= 'A')&&(dData <= 'F'))
				rst =  dData+10-'A';
	else if((dData >= 'a')&&(dData <= 'f'))
				rst =  dData+10-'a';
	else rst = 0;//不是ASCII的char就返回0 有点儿欠妥！
			
	return rst;
}
//一共3个方法啦！！！
//"1234"--->0X12,0X34 
void BAIDUhex_to_decimal(const char *hex_string, unsigned char *arr, size_t arr_len)
{
    const char *pos = hex_string;
    int count;

    for (count = 0; count < arr_len; count++) {
        sscanf(pos, "%2hhx", &arr[count]);
        pos += 2;
    }
}
//压缩一半
//完成"10"--->0x10  "1234"--->0X12,0X34 
//len标识传入的strlen(strings)
//返回值是len的一半
char G_strsTobytes(void* Strings,void* Bytes,char len)
{
	unsigned char* strings=(unsigned char *)Strings;
	unsigned char* bytes  =(unsigned char *)Bytes;
	unsigned char i = 0,j=0,lowbits=0,highbits=0;
	if(len%2)return 0;//禁止奇数
	for (i = 0; i < len; i+=2)
	{           
		highbits = G_strTobyte(strings[i]  );
		lowbits  = G_strTobyte(strings[i+1]);
		bytes[j++] =( highbits << 4)|lowbits;
	}
	return j;
}
//完成"10"--->0x10  "1234"--->0X12,0X34 
//功能和上面一样 这个是机智云源码
void G_strsTohexs(char *pbSrc,char *pbDest,int32_t nLen)
{
    char h1,h2;
    char s1,s2;
    int32_t i;

    for (i=0; i<nLen; i++)
    {
        h1 = pbSrc[2*i];
        h2 = pbSrc[2*i+1];

        s1 = toupper(h1) - 0x30;//技巧1 直接减去0X30也就是减去‘0’
        if (s1 > 9)             //技巧2 toupper直接把char变成大写 也就避免了小写的case 
            s1 -= 7;            //技巧3 如果是ABC字符的话在-0x30的基础上再-7 7怎么来的？ASCII表A--65 9--57

        s2 = toupper(h2) - 0x30;
        if (s2 > 9)
            s2 -= 7;

        pbDest[i] = s1*16 + s2;//不如s1<<4 | s2
    }
}

//0XAB-->"AB" 长度会扩大一倍！注意：0没有结束符
void G_1byteTo2str(unsigned char* strings,unsigned char* bytes,unsigned char len)
{
    unsigned char const StrRefer[]="0123456789abcdef";//"0123456789ABCDEF";
    #define GET_MSB_STR(x) (StrRefer[((x>>4)&0x0f)])
    #define GET_LSB_STR(x) (StrRefer[(x&0x0f)])
    for(char i=0,j=0;i<len;i++,j+=2)
    {
        strings[j]  =GET_MSB_STR(bytes[i]);
        strings[j+1]=GET_LSB_STR(bytes[i]);
    }

}

//下面是机智云版本：
//最后出来的Str的长度是进去的hex的2倍+1
void  G_hex2Str(unsigned char *pbDest, unsigned char *pbSrc, int32_t nLen)
{
    char    ddl,ddh;
    int32_t i;

    for (i=0; i<nLen; i++) 
	{
        ddh = 0x30 + pbSrc[i] / 16;
        ddl = 0x30 + pbSrc[i] % 16;
        if (ddh > 0x39) ddh = ddh + 7;
        if (ddl > 0x39) ddl = ddl + 7;
        pbDest[i*2] = ddh;
        pbDest[i*2+1] = ddl;
    }

    pbDest[nLen*2] = '\0';
}






