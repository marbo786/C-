#include<iostream>
using namespace std;
int main()
{
	char arr[2]={'-','*',};
    for(int i=1;i<=24;i++)// Number of lines code will run
	{
		//outer left layer
		if(i>=1&&i<=8)
		{
			for(int k=0;k<(9-i);k++)//External left spacing for first 8 lines
			{
				cout<<" ";
			}
		}
		else if(i>=17&&i<=24)//External left spacing for last 8 lines
		{
			for(int k=0;k<(i-16);k++)
			{
				cout<<" ";
			}
		}
		//outer layer of shape on left side
		cout<<arr[i%2];
		if(i>2&&i<23)
		{
			cout<<" ";
			cout<<arr[(i+1)%2];
			if(i>=4&&i<=7)//inner space and layer of shape
			{
				for(int k=0;k<(((i-3)*2)-1);k++)// Most internal spacing for upper half
				{
					cout<<" ";
				}
			}
			else if(i>=17&&i<=24)
			{
				for(int k=(((i-16)*2)-1);k<10;k++)//Most internal spacing for lower half
				{
					cout<<" ";
           		}
			}
			else if(i>=8&&i<=16)
			{
			if(i>8)
			cout<<" ";
			if(i<=12)//internal box code
			{
				for(int k=0;k<(12-i);k++)
				{
					cout<<arr[1];//left stericks
				}
				for(int k=0;k<(i-7);k++)
				{
					cout<<(k+1);//left numbers upto the maximum
				}
				for(int k=0;k<(i-8);k++)//right descending numbers
				{
					cout<<((i-8)-k);
				}
				for(int k=0;k<(12-i);k++)//right stericks
				{
					cout<<arr[1];
				}
			}
			else
			{
				for(int k=0;k<(i-12);k++)
				{
					cout<<arr[1];
				}
				for(int k=1;k<(18-i);k++)
				{
					cout<<k;
				}
				for(int k=2;k<(18-i);k++)
				{
					cout<<" ";
				}
					for(int k=0;k<(i-12);k++)
				{
					cout<<arr[1];
				}
			}
			}
			}
			if(i>=4&&i<=21)//right internal space after internal layer
			{
				if(i>=9&&i<=16)
				{
				cout<<" ";
				}
				cout<<arr[((i+1)%2)];//most right layer of outer layer
			}
			if(i>=2&&i<=23)
			{
			cout<<" ";
			cout<<arr[i%2];
		    }  
	        cout<<endl;
}
return 0;
}