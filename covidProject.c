#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>
#include<windows.h>

void national();
void international();

void stateAndGivenDate(FILE *fp,const char* state,char date[],int option);
//void districtAndGivenDate(FILE *fp,char district[],char date[],int option);
void unionTerritoriesAndGivenDate(FILE *fp,const char* unionTerritories,char date[],int option);
void IndianCases(FILE *fp,char date[]);
const char* stateSelection(int number);
const char* unionTerritoriesSelection(int number);

void countryAndGivenDate(FILE *fp,char country[],char date[]);
void countryAndPresentDate(FILE *fp,char country[]);
void continentAndGivenDate(FILE *fp,const char* continent,char date[]);
void WorldwideCases(FILE *fp,char date[]);
const char* continentSelection(int number);

void deathRate(FILE *fp,const char* startDate,const char* endDate,const char* state);
void recoveryRate(FILE *fp,const char* startDate,const char* endDate,const char* state);
void deathRateByDay(FILE *fp,char date[],const char* state);
void recoveryRateByDay(FILE *fp,char date[],const char* state);

const char* monthStartDate(int month);
const char* monthEndDate(int month);

void SetColor(int ForgC)//to set color of console background
{
     WORD wColor;
     ///We will need this handle to get the current background attribute
     HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
     CONSOLE_SCREEN_BUFFER_INFO csbi;

     ///We use csbi for the wAttributes word.
     if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
     {
        ///Mask out all but the background attribute, and add in the forgournd color
          wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
          SetConsoleTextAttribute(hStdOut, wColor);
     }
     return;
}

int main(){
	int location;
	system("color 8e");
	while(1){
		system("cls");
		printf("\t\t\t\t\t\t\t\t***********************\n");
		printf("\t\t\t\t\t\t\t\t* COVID CASES TRACKER *\n");
		printf("\t\t\t\t\t\t\t\t***********************\n");
		printf("\n1.National data\n");
		printf("2.International data\n");
		printf("3.Exit\n");
		printf("Enter corresponding number:");
		scanf("%d",&location);
		if(location>=3){break;}
		system("cls");
		if(location==1){
			national();
		}
		else if(location==2){
			international();
		}
	}
}
void stateAndGivenDate(FILE *fp,const char* state,char date[],int option){
	fseek(fp,0,SEEK_SET);
	char buf[1000];
	char *token;
	char *arr[1000];
	int j;
	int flag=0;
	int datePresent=0;
	for(int i=0;i<8500;i++){
		j=0;
		if(fgets(buf,1000,fp)!=NULL){
			token = strtok(buf,",");
			while(token!= NULL){
				arr[j++]=token;
				token = strtok(NULL,",");
			}
			if(!strcmp(arr[1],date)){datePresent=1;}
			if(!strcmp(arr[2],state) && !strcmp(arr[1],date)){
				if(option==1){
					printf("\t\t__________________________________\n\n");
					printf("\t\t Total cases in %s: %d\n",state,atoi(arr[3]));
					printf("\t\t__________________________________\n\n");
				}
				else if(option==2){
					printf("\t\t__________________________________\n\n");
					printf("\t\t Active cases in %s: %d\n",state,atoi(arr[4]));
					printf("\t\t__________________________________\n\n");
				}
				else if(option==3){
					printf("\t\t__________________________________\n\n");
					printf("\t\tTotal Deaths in %s: %d\n",state,atoi(arr[6]));
					printf("\t\t__________________________________\n\n");
				}
				else if(option==4){
					printf("\t\t__________________________________\n\n");
					printf("\t\tTotal Recoveries in %s: %d\n",state,atoi(arr[5]));
					printf("\t\t__________________________________\n\n");
				}
				flag = 1;
				break;
			}
		}
		/*else{
			printf("NULL");
		}*/
	}
	if(flag==0 && datePresent==1){
		//printf("No data for given inputs\n");
		if(option==1){
				printf("\t\t__________________________________\n\n");
				printf("\t\t Total cases in %s: 0\n",state);
				printf("\t\t__________________________________\n\n");
			}
			else if(option==2){
				printf("\t\t__________________________________\n\n");
				printf("\t\tTotal Deaths in %s: 0\n",state);
				printf("\t\t__________________________________\n\n");
			}
			else if(option==3){
				printf("\t\t__________________________________\n\n");
				printf("\t\tTotal Recoveries in %s: 0\n",state);
				printf("\t\t__________________________________\n\n");
			}
	}
	else if(flag==0){printf("No data for given inputs\n");}
}
void IndianCases(FILE *fp,char date[]){
	fseek(fp,0,SEEK_SET);
	char buf[1000];
	char *token;
	char *arr[1000];
	int j;
	int flag=0;
	int totalCases=0,totalDeaths=0,totalRecoveries=0,activeCases=0;
	for(int i=0;i<8500;i++){
		j=0;
		if(fgets(buf,1000,fp)!=NULL){
			token = strtok(buf,",");
			while(token!= NULL){
				arr[j++]=token;
				token = strtok(NULL,",");
				//printf("%s-",arr[j-1]);
			}
			char name[10]="India";
			if(!strcmp(arr[1],date) && !strcmp(arr[2],name)){
				totalCases=atoi(arr[3]);
				activeCases=atoi(arr[4]);
				totalRecoveries=atoi(arr[5]);
				totalDeaths=atoi(arr[6]);
				flag = 1;
			}
		}
	}
	printf("\t\t______________________________________\n");
	printf("\n\t\tTotal Cases in India: %d\n",totalCases);
	printf("\t\t______________________________________\n");
	printf("\n\t\tActive Cases in India: %d\n",activeCases);
	printf("\t\t______________________________________\n");
	printf("\n\t\tTotal Recoveries in India: %d\n",totalRecoveries);
	printf("\t\t______________________________________\n");
	printf("\n\t\tTotal Deaths in India: %d\n",totalDeaths);
	printf("\t\t______________________________________\n");
	if(flag==0){
			printf("No data for given inputs\n");
	}
}
void unionTerritoriesAndGivenDate(FILE *fp,const char* unionTerritories,char date[],int option){
	fseek(fp,0,SEEK_SET);
	char buf[1000];
	char *token;
	char *arr[1000];
	int j;
	int flag=0;
	for(int i=0;i<8500;i++){
		j=0;
		if(fgets(buf,1000,fp)!=NULL){
			token = strtok(buf,",");
			while(token!= NULL){
				arr[j++]=token;
				token = strtok(NULL,",");
			}
			if(!strcmp(arr[2],unionTerritories) && !strcmp(arr[1],date)){
				if(option==1){
					printf("\t\t__________________________________\n\n");
					printf("\t\t Total cases in %s: %d\n",unionTerritories,atoi(arr[3]));
					printf("\t\t__________________________________\n\n");
				}
				if(option==2){
					printf("\t\t__________________________________\n\n");
					printf("\t\t Active cases in %s: %d\n",unionTerritories,atoi(arr[4]));
					printf("\t\t__________________________________\n\n");
				}
				else if(option==3){
					printf("\t\t__________________________________\n\n");
					printf("\t\tTotal Deaths in %s: %d\n",unionTerritories,atoi(arr[6]));
					printf("\t\t__________________________________\n\n");
				}
				else if(option==4){
					printf("\t\t__________________________________\n\n");
					printf("\t\tTotal Recoveries in %s: %d\n",unionTerritories,atoi(arr[5]));
					printf("\t\t__________________________________\n\n");
				}
				flag = 1;
				break;
			}
		}
		/*else{
			printf("NULL");
		}*/
	}
	if(flag==0){
			printf("No data for given inputs\n");
		}
}
const char* stateSelection(int number){
	if(number==1)
		return "Andhra Pradesh";
	else if(number==2)
		return "Arunachal Pradesh";
	else if(number==3)
		return "Assam";
	else if(number==4)
		return "Bihar";
	else if(number==5)
		return "Chhattisgarh";
	else if(number==6)
		return "Goa";
	else if(number==7)
		return "Gujarat";
	else if(number==8)
		return "Haryana";
	else if(number==9)
		return "Himachal Pradesh";
	else if(number==10)
		return "Jharkhand";
	else if(number==11)
		return "Karnataka";
	else if(number==12)
		return "Kerala";
	else if(number==13)
		return "Madhya Pradesh";
	else if(number==14)
		return "Maharashtra";
	else if(number==15)
		return "Manipur";
	else if(number==16)
		return "Meghalaya";
	else if(number==17)
		return "Mizoram";
	else if(number==18)
		return "Nagaland";
	else if(number==19)
		return "Odisha";
	else if(number==20)
		return "Punjab";
	else if(number==21)
		return "Rajasthan";
	else if(number==22)
		return "Sikkim";
	else if(number==23)
		return "Tamil Nadu";
	else if(number==24)
		return "Telangana";
	else if(number==25)
		return "Tripura";
	else if(number==26)
		return "Uttar Pradesh";
	else if(number==27)
		return "Uttarakhand";
	else if(number==28)
		return "West Bengal";
	else if(number==29)
		return "Jammu and Kashmir";
}
const char* unionTerritoriesSelection(int number){
	if(number==1)
		return "Andaman and Nicobar Islands";
	else if(number==2)
		return "Chandigarh";
	else if(number==3)
		return "Dadra and Nagar Haveli and Daman and Diu";
	else if(number==4)
		return "Delhi";
	else if(number==5)
		return "Ladakh";
	else if(number==6)
		return "Lakshadweep";
	else if(number==7)
		return "Puducherry";
}

void countryAndGivenDate(FILE *fp,char country[],char date[]){
	fseek(fp,0,SEEK_SET);
	char buf[1000];
	char *token;
	char *arr[1000];
	int j;
	int flag=0;
	for(int i=0;i<57000;i++){
		j=0;
		if(fgets(buf,1000,fp)!=NULL){
			token = strtok(buf,",");
			while(token!= NULL){
				arr[j++]=token;
				token = strtok(NULL,",");
			}
			if(!strcmp(arr[2],country) && !strcmp(arr[3],date)){
				printf("\t\t__________________________________\n\n");
				printf("\t\tTotal cases in %s:%d\n",arr[2],atoi(arr[4]));
				printf("\t\t__________________________________\n\n");
				printf("\t\tTotal deaths in %s:%d\n",arr[2],atoi(arr[7]));
				printf("\t\t__________________________________\n\n");
				flag = 1;
				break;
			}
		}
		else{
			printf("NULL");
		}
	}
	if(flag==0){
			printf("No data for given inputs\n");
		}
}
void continentAndGivenDate(FILE *fp,const char* continent,char date[]){
	fseek(fp,0,SEEK_SET);
	char buf[1000];
	char *token;
	char *arr[1000];
	int j;
	int flag=0;
	int t_count=0,r_count=0,d_count=0;
	for(int i=0;i<57000;i++){
		j=0;
		if(fgets(buf,1000,fp)!=NULL){
			token = strtok(buf,",");
			while(token!= NULL){
				arr[j++]=token;
				token = strtok(NULL,",");
			}
			int cases;
			if(!strcmp(arr[1],continent) && !strcmp(arr[3],date)){
				cases=atoi(arr[4]);
				t_count+=cases;
				d_count+=atoi(arr[7]);
				flag = 1;
			}
		}
		else{
			printf("NULL");
		}
	}
	if(flag==1){
		printf("\t\t__________________________________\n\n");
		printf("\t\tTotal Cases in %s : %d\n",continent,t_count);
		printf("\t\t__________________________________\n\n");
		printf("\t\tTotal Deaths in %s : %d\n",continent,d_count);
		printf("\t\t__________________________________\n\n");
	}
	if(flag==0){
			printf("No data for given inputs\n");
	}
}
void WorldwideCases(FILE *fp,char date[]){
	fseek(fp,0,SEEK_SET);
	char buf[1000];
	char *token;
	char *arr[1000];
	int j;
	int flag=0;
	int count=0;
	for(int i=0;i<57000;i++){
		j=0;
		if(fgets(buf,1000,fp)!=NULL){
			token = strtok(buf,",");
			while(token!= NULL){
				arr[j++]=token;
				token = strtok(NULL,",");
				//printf("%s-",arr[j-1]);
			}
			char all[10]="World";
			if(!strcmp(arr[1],all) && !strcmp(arr[2],date)){
				printf("Worldwide Total Cases:%d\n",atoi(arr[3]));
				flag = 1;
				break;
			}
		}
		else{
			printf("NULL");
		}
	}
	if(flag==0){
			printf("No data for given inputs\n");
	}
}
const char* continentSelection(int number){
	if(number==1)
		return "Asia";
	else if(number==2)
		return "Africa";
	else if(number==3)
		return "Oceania";
	else if(number==4)
		return "Antarctica";
	else if(number==5)
		return "Europe";
	else if(number==6)
		return "North America";
	else if(number==7)
		return "South America";
}

void national(){
	char date[50];
	int n=0;
	char present_date[15]="27/11/2020";//file last updated on 1/12/2020
	FILE *fp = fopen("COVID-19 Cases(01-12-2020).csv","r");
	if(fp==NULL){
	printf("No file");
	}
	char state[50];
	int m,a,b;
	int num,month;
	printf("\t\t\t\t\t\t\t\t***********************\n");
	printf("\t\t\t\t\t\t\t\t* COVID CASES TRACKER *\n");
	printf("\t\t\t\t\t\t\t\t***********************\n");
	while(n<8){
		printf("\n\n1.Know the Present Indian Cases\n");
		printf("2.Get Data By State and given date\n");
		printf("3.Get Data By State and present date\n");
		printf("4.Get Data By Union Territories and given date\n");
		printf("5.Get Data By Union Territories and present date\n");
		printf("6.Know Death Rate\n");
		printf("7.Know Recovery Rate\n");
		printf("8.Exit\n");
		printf("Enter the corresponding number:");
		scanf("%d",&n);
		switch(n){
			case 1:
				printf("\n\t\t1.Know by given date\n");
				printf("\t\t2.Know by present date\n");
				printf("\t\tEnter corresponding number:");
				scanf("%d",&m);
				if (m==1){
					printf("\nEnter date to know the Total Indian cases(dd/mm/yyyy):");
					scanf("%s",&date);
				}
				else if(m==2){strcpy(date,present_date);}
				IndianCases(fp,date);
				break;
			case 2:
				system("cls");
				printf("\n_____________________\n\n1.Andhra Pradesh\n2.Arunachal Pradesh\n3.Assam\n4.Bihar\n5.Chhattisgarh\n6.Goa\n7.Gujarat\n8.Haryana\n9.Himachal Pradesh\n10.Jharkhand\n11.Karnataka\n12.Kerala\n13.Madhya Pradesh\n14.Maharashtra\n15.Manipur\n16.Meghalaya\n17.Mizoram\n18.Nagaland\n19.Odisha\n20.Punjab\n21.Rajasthan\n22.Sikkim\n23.Tamil Nadu\n24.Telangana\n25.Tripura\n26.Uttar Pradesh\n27.Uttarakhand\n28.West Bengal\n29.Jammu and Kashmir\n_____________________\n\n");
				printf("Enter corresponding number:");
				scanf("%d",&num);
				printf("Enter date(dd/mm/yyyy):");
				scanf("%s",&date);
				printf("\n\t\t1.Know total cases\n");
				printf("\t\t2.Know active cases\n");
				printf("\t\t3.Know deaths\n");
				printf("\t\t4.Know recoveries\n");
				printf("\t\tOption:");
				scanf("%d",&m);
				stateAndGivenDate(fp,stateSelection(num),date,m);
				break;
			case 3:
				system("cls");
				printf("\n_____________________\n\n1.Andhra Pradesh\n2.Arunachal Pradesh\n3.Assam\n4.Bihar\n5.Chhattisgarh\n6.Goa\n7.Gujarat\n8.Haryana\n9.Himachal Pradesh\n10.Jharkhand\n11.Karnataka\n12.Kerala\n13.Madhya Pradesh\n14.Maharashtra\n15.Manipur\n16.Meghalaya\n17.Mizoram\n18.Nagaland\n19.Odisha\n20.Punjab\n21.Rajasthan\n22.Sikkim\n23.Tamil Nadu\n24.Telangana\n25.Tripura\n26.Uttar Pradesh\n27.Uttarakhand\n28.West Bengal\n29.Jammu and Kashmir\n_____________________\n\n");
				printf("Enter corresponding number:");
				scanf("%d",&num);
				printf("\n\t\t1.Know total cases\n");
				printf("\t\t2.Know active cases\n");
				printf("\t\t3.Know deaths\n");
				printf("\t\t4.Know recoveries\n");
				printf("\t\tOption:");
				scanf("%d",&m);
				stateAndGivenDate(fp,stateSelection(num),present_date,m);
				break;
			case 4:
				system("cls");
				printf("\n_____________________\n\n1.Andaman and Nicobar\n2.Chandigarh\n3.Dadra and Nagar Haveli and Daman and Diu\n4.Delhi\n5.Ladakh\n6.Lakshadweep*\n7.Puducherry\n_____________________\n\n");
				printf("Enter corresponding number:");
				scanf("%d",&num);
				printf("Enter date(dd/mm/yyyy):");
				scanf("%s",&date);
				printf("\n\t\t1.Know total cases\n");
				printf("\t\t2.Know active cases\n");
				printf("\t\t3.Know deaths\n");
				printf("\t\t4.Know recoveries\n");
				printf("\t\tOption:");
				scanf("%d",&m);
				unionTerritoriesAndGivenDate(fp,unionTerritoriesSelection(num),date,m);
				break;
			case 5:
				system("cls");
				printf("\n_____________________\n\n1.Andaman and Nicobar\n2.Chandigarh\n3.Dadra and Nagar Haveli and Daman and Diu\n4.Delhi\n5.Ladakh\n6.Lakshadweep\n7.Puducherry\n_____________________\n\n");
				printf("Enter corresponding number:");
				scanf("%d",&num);
				printf("\n\t\t1.Know total cases\n");
				printf("\t\t2.Know active cases\n");
				printf("\t\t3.Know deaths\n");
				printf("\t\t4.Know recoveries\n");
				printf("\t\tOption:");
				scanf("%d",&m);
				unionTerritoriesAndGivenDate(fp,unionTerritoriesSelection(num),present_date,m);
				break;
			case 6:
				printf("1.For State\n");
				printf("2.For Union Territory\n");
				printf("Enter corresponding number:");
				scanf("%d",&a);
				system("cls");
				if(a==1){
					printf("Which State?\n");
					printf("\n_____________________\n\n1.Andhra Pradesh\n2.Arunachal Pradesh\n3.Assam\n4.Bihar\n5.Chhattisgarh\n6.Goa\n7.Gujarat\n8.Haryana\n9.Himachal Pradesh\n10.Jharkhand\n11.Karnataka\n12.Kerala\n13.Madhya Pradesh\n14.Maharashtra\n15.Manipur\n16.Meghalaya\n17.Mizoram\n18.Nagaland\n19.Odisha\n20.Punjab\n21.Rajasthan\n22.Sikkim\n23.Tamil Nadu\n24.Telangana\n25.Tripura\n26.Uttar Pradesh\n27.Uttarakhand\n28.West Bengal\n29.Jammu and Kashmir\n_____________________\n\n");
					printf("Enter corresponding number:");
					scanf("%d",&num);
				}
				else if(a==2){
					printf("Which Union Territory?\n");
					printf("\n_____________________\n\n1.Andaman and Nicobar\n2.Chandigarh\n3.Dadra and Nagar Haveli and Daman and Diu\n4.Delhi\n5.Ladakh\n6.Lakshadweep\n7.Puducherry\n_____________________\n\n");
					printf("Enter corresponding number:");
					scanf("%d",&num);
				}
				/*printf("Enter start date(dd/mm/yyy):");
				scanf("%s",&startDate);
				printf("Enter end date(dd/mm/yyy):");
				scanf("%s",&endDate);
				*/
				printf("1.By Month\n");
				printf("2.By Date\n");
				scanf("%d",&b);
				if(b==1){
					printf("Which month?\n");
					printf("\n_____________________\n\n1.January\n2.February\n3.March\n4.April\n5.May\n6.June\n7.July\n8.August\n9.September\n10.October\n11.November\n12.December\n_____________________\n\n");
					printf("Enter corresponding number:\n");
					scanf("%d",&month);
				}
				else if(b==2){
					printf("Enter Date:");
					scanf("%s",&date);
				}
				if(a==1 && b==1){deathRate(fp,monthStartDate(month),monthEndDate(month),stateSelection(num));}
				else if(a==2&& b==1){deathRate(fp,monthStartDate(month),monthEndDate(month),unionTerritoriesSelection(num));}
				else if(a==1&& b==2){deathRateByDay(fp,date,stateSelection(num));}
				else if(a==2&& b==2){deathRateByDay(fp,date,unionTerritoriesSelection(num));}
				break;
			case 7:
				printf("1.For State\n");
				printf("2.For Union Territory\n");
				printf("Enter corresponding number:");
				scanf("%d",&a);
				system("cls");
				if(a==1){
					printf("Which State?\n");
					printf("\n_____________________\n\n1.Andhra Pradesh\n2.Arunachal Pradesh\n3.Assam\n4.Bihar\n5.Chhattisgarh\n6.Goa\n7.Gujarat\n8.Haryana\n9.Himachal Pradesh\n10.Jharkhand\n11.Karnataka\n12.Kerala\n13.Madhya Pradesh\n14.Maharashtra\n15.Manipur\n16.Meghalaya\n17.Mizoram\n18.Nagaland\n19.Odisha\n20.Punjab\n21.Rajasthan\n22.Sikkim\n23.Tamil Nadu\n24.Telangana\n25.Tripura\n26.Uttar Pradesh\n27.Uttarakhand\n28.West Bengal\n29.Jammu and Kashmir\n_____________________\n\n");
					printf("Enter corresponding number:");
					scanf("%d",&num);
				}
				else if(a==2){
					printf("Which Union Territory?\n");
					printf("\n_____________________\n\n1.Andaman and Nicobar\n2.Chandigarh\n3.Dadra and Nagar Haveli and Daman and Diu\n4.Delhi\n5.Ladakh\n6.Lakshadweep\n7.Puducherry\n_____________________\n\n");
					printf("Enter corresponding number:");
					scanf("%d",&num);
				}
				/*printf("Enter start date(dd/mm/yyy):");
				scanf("%s",&startDate);
				printf("Enter end date(dd/mm/yyy):");
				scanf("%s",&endDate);
				*/
				system("cls");
				printf("1.By Month\n");
				printf("1.By Date\n");
				scanf("%d",&b);
				if(b==1){
					printf("Which month?\n");
					printf("\n_____________________\n\n1.January\n2.February\n3.March\n4.April\n5.May\n6.June\n7.July\n8.August\n9.September\n10.October\n11.November\n12.December\n_____________________\n\n");
					printf("Enter corresponding number:\n");
					scanf("%d",&month);
				}
				else if(b==2){
					printf("Enter Date:");
					scanf("%s",&date);
				}
				if(a==1 && b==1){recoveryRate(fp,monthStartDate(month),monthEndDate(month),stateSelection(num));}
				else if(a==2&& b==1){recoveryRate(fp,monthStartDate(month),monthEndDate(month),unionTerritoriesSelection(num));}
				else if(a==1&& b==2){recoveryRateByDay(fp,date,stateSelection(num));}
				else if(a==2&& b==2){recoveryRateByDay(fp,date,unionTerritoriesSelection(num));}
				break;
		}
	}
}
void international(){
	char date[50];
	int n=0;
	char present_date[15]="2020-11-30";//last updates on 2020-11-30
	FILE *fp = fopen("owid-covid-data.csv","r");
	if(fp==NULL){
		printf("No file");
	}
	char country[50];
	char continent[50];
	printf("\t\t\t\t\t\t\t\t***********************\n");
	printf("\t\t\t\t\t\t\t\t* COVID CASES TRACKER *\n");
	printf("\t\t\t\t\t\t\t\t***********************\n");
	while(n<5){
		//printf("1.Know the Present Worldwide Cases.\n");
		printf("Get data:\n");
		printf("1.By Country and given date\n");
		printf("2.By Country and present date\n");
		printf("3.By Continent and given date\n");
		printf("4.By Continent and present date\n");
		printf("5.Exit\n");
		printf("Enter the corresponding number:");
		scanf("%d",&n);
		system("cls");
		printf("\t\t\t\t\t\t\t\t***********************\n");
		printf("\t\t\t\t\t\t\t\t* COVID CASES TRACKER *\n");
		printf("\t\t\t\t\t\t\t\t***********************\n");
		int a;
		switch(n){
			/*case 1:printf("\nEnter date to know the Worldwide cases(yyyy-mm-dd):");
				scanf("%s",&date);
				WorldwideCases(fp,date);
				break;
				*/
			case 1:printf("\nEnter country name(enter first letter capital for each word):");
				scanf("%s",&country);
				printf("Enter date(yyyy-mm-dd):");
				scanf("%s",&date);
				countryAndGivenDate(fp,country,date);
				break;
			case 2:printf("\nEnter country name(enter first letter capital for each word):");
				scanf("%s",&country);
				countryAndGivenDate(fp,country,present_date);
				break;
			case 3:printf("\n_____________________\n\n1.Asia\n2.Africa\n3.Australia\n4.Antarctica\n5.Europe\n6.North America\n7.South America\n_____________________\n\n");
				printf("Enter corresponding number:");
				scanf("%d",&a);
				printf("Enter date(yyyy-mm-dd):");
				scanf("%s",&date);
				continentAndGivenDate(fp,continentSelection(a),date);
				break;
			case 4:printf("\n_____________________\n\n1.Asia\n2.Africa\n3.Australia\n4.Antarctica\n5.Europe\n6.North America\n7.South America\n_____________________\n\n");
				printf("Enter corresponding number:");
				scanf("%d",&a);
				continentAndGivenDate(fp,continentSelection(a),present_date);				
				break;
		}
	}	
}

void deathRate(FILE *fp,const char* startDate,const char* endDate,const char* state){
	fseek(fp,0,SEEK_SET);
	char buf[1000];
	char *token;
	char *arr[1000];
	int j;
	int flag=0;
	int startTotalCases,endTotalCases,startDeaths,endDeaths;
	for(int i=0;i<8500;i++){
		j=0;
		if(fgets(buf,1000,fp)!=NULL){
			token = strtok(buf,",");
			while(token!= NULL){
				arr[j++]=token;
				token = strtok(NULL,",");
			}
			if(!strcmp(arr[2],state)){
				if(!strcmp(arr[1],startDate)){
					startTotalCases=atoi(arr[3]);
					startDeaths=atoi(arr[6]);
				}
				if(!strcmp(arr[1],endDate)){
					endTotalCases=atoi(arr[3]);
					endDeaths=atoi(arr[6]);	
				}				
				flag = 1;
				break;
			}
		}
		/*else{
			printf("NULL");
		}*/
	}
	if(flag==0){
			printf("No data for given inputs\n");
		}
	else{
		printf("\n\t\t________________________________________________________________________\n\n");
		printf("\t\tDeath rate between %s and %s in %s : %.2f%%",startDate,endDate,state,(((float)(endDeaths-startDeaths))*100)/(endTotalCases-startTotalCases));
		printf("\n\t\t________________________________________________________________________\n\n");
	}
}

void recoveryRate(FILE *fp,const char* startDate,const char* endDate,const char* state){
	fseek(fp,0,SEEK_SET);
	char buf[1000];
	char *token;
	char *arr[1000];
	int j;
	int flag=0;
	int startTotalCases,endTotalCases,startRecoveries,endRecoveries;
	for(int i=0;i<8500;i++){
		j=0;
		if(fgets(buf,1000,fp)!=NULL){
			token = strtok(buf,",");
			while(token!= NULL){
				arr[j++]=token;
				token = strtok(NULL,",");
			}
			if(!strcmp(arr[2],state)){
				if(!strcmp(arr[1],startDate)){
					startTotalCases=atoi(arr[3]);
					startRecoveries=atoi(arr[5]);
				}
				if(!strcmp(arr[1],endDate)){
					endTotalCases=atoi(arr[3]);
					endRecoveries=atoi(arr[5]);	
				}				
				flag = 1;
			}
		}
		/*else{
			printf("NULL");
		}*/
	}
	if(flag==0){
			printf("No data for given inputs\n");
		}
	else{
		printf("\n\t\t________________________________________________________________________\n\n");
		printf("\t\tRecovery rate between %s and %s in %s : %.2f%%",startDate,endDate,state,(((float)(endRecoveries-startRecoveries))*100)/(endTotalCases-startTotalCases));
		printf("\n\t\t________________________________________________________________________\n\n");
	}
}

const char* monthStartDate(int month){
	switch(month){
		case 1:
			return "01/01/2020";
			break;
		case 2:
			return "01/02/2020";
			break;
		case 3:
			return "01/03/2020";
			break;
		case 4:
			return "01/04/2020";
			break;
		case 5:
			return "01/05/2020";
			break;
		case 6:
			return "01/06/2020";
			break;
		case 7:
			return "01/07/2020";
			break;
		case 8:
			return "01/08/2020";
			break;
		case 9:
			return "01/09/2020";
			break;
		case 10:
			return "01/10/2020";
			break;
		case 11:
			return "01/11/2020";
			break;
		case 12:
			return "01/12/2020";
			break;
	}
	return 0;
}

const char* monthEndDate(int month){
	switch(month){
		case 1:
			return "31/01/2020";
			break;
		case 2:
			return "29/02/2020";
			break;
		case 3:
			return "31/03/2020";
			break;
		case 4:
			return "30/04/2020";
			break;
		case 5:
			return "31/05/2020";
			break;
		case 6:
			return "30/06/2020";
			break;
		case 7:
			return "31/07/2020";
			break;
		case 8:
			return "31/08/2020";
			break;
		case 9:
			return "30/09/2020";
			break;
		case 10:
			return "31/10/2020";
			break;
		case 11:
			return "30/11/2020";
			break;
		case 12:
			return "31/12/2020";
			break;
	}
	return 0;
}

void recoveryRateByDay(FILE *fp,char date[],const char* state){
	fseek(fp,0,SEEK_SET);
	char buf[1000];
	char *token;
	char *arr[1000];
	int j;
	int flag=0;
	for(int i=0;i<8500;i++){
		j=0;
		if(fgets(buf,1000,fp)!=NULL){
			token = strtok(buf,",");
			while(token!= NULL){
				arr[j++]=token;
				token = strtok(NULL,",");
			}
			if(!strcmp(arr[2],state)){
				if(!strcmp(arr[1],date)){
					printf("\n\t\t________________________________________________________________________\n\n");
					printf("\t\tRecovery rate on %s in %s : %.2f%%",date,state,(((float)(atoi(arr[5])))*100)/(atoi(arr[3])));
					printf("\n\t\t________________________________________________________________________\n\n");
				}			
				flag = 1;
			}
		}
		/*else{
			printf("NULL");
		}*/
	}
	if(flag==0){
			printf("No data for given inputs\n");
		}
}

void deathRateByDay(FILE *fp,char date[],const char* state){
	fseek(fp,0,SEEK_SET);
	char buf[1000];
	char *token;
	char *arr[1000];
	int j;
	int flag=0;
	for(int i=0;i<8500;i++){
		j=0;
		if(fgets(buf,1000,fp)!=NULL){
			token = strtok(buf,",");
			while(token!= NULL){
				arr[j++]=token;
				token = strtok(NULL,",");
			}
			if(!strcmp(arr[2],state)){
				if(!strcmp(arr[1],date)){
					printf("\n\t\t________________________________________________________________________\n\n");
					printf("\t\tDeath rate on %s in %s : %.2f%%",date,state,(((float)(atoi(arr[6])))*100)/(atoi(arr[3])));
					printf("\n\t\t________________________________________________________________________\n\n");
				}			
				flag = 1;
			}
		}
		/*else{
			printf("NULL");
		}*/
	}
	if(flag==0){
			printf("No data for given inputs\n");
		}
}