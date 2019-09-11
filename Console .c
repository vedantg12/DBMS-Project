#include <stdio.h>

#include <stdlib.h>

#include <libpq-fe.h>

#include <string.h>


int main() {

	
PGconn          *conn;
	
PGresult        *res;
	
int             rec_count;
	
int             row;
	
int             col;
	
conn = PQconnectdb("host=10.100.71.21 port=5432 user=201601179 password=dar643673 dbname=201601179");

	
if (PQstatus(conn) == CONNECTION_BAD) {
		
					puts("We were unable to connect to the database");
		
					exit(0);
	
					}
	
char *string=(char *)malloc(1000*sizeof(char));

while(1)
{
	
	res=PQexec(conn,"set search_path to \"fbl\";");

		printf("enter 1 for query 2 for update then enter the sql string and 3 for exit\n");
	
		int type;
	
		scanf("%d\n",&type);
	
		fflush(stdout);
	if(type==1)
	
		{	scanf("%[^\n]s",string);
		
			res = PQexec(conn,string);

		
				if (PQresultStatus(res) != PGRES_TUPLES_OK) 
				{
			
					printf("%s",PQresultErrorMessage(res));
			
					continue;
		
				}
		
			rec_count = PQntuples(res);
		
			printf("We received %d records.\n", rec_count);
		
			puts("==========================");
		
			int col_count=PQnfields(res);
		
			for (col=0; col<col_count; col++) 
			{
			
				printf("%s\t", PQfname(res,col));
		
			}
		
			puts("");

		
			for (row=0; row<rec_count; row++) 
			{
			
				for (col=0; col<col_count; col++) 
				{
				
					printf("%s\t", PQgetvalue(res, row, col));
			
				}
			
				puts("");
		
			}

		
			puts("==========================");
	
			}
	
			else if(type==2)
	
			{
		
				scanf("%[^\n]s",string);
		
				res = PQexec(conn,string);

		
				if (PQresultStatus(res) != PGRES_COMMAND_OK) 
				{
			
					printf("%s",PQresultErrorMessage(res));
                        
					continue;
		
				}
		
				else
		
				{
			
					printf("Update query executed succesfully\n");
		
				}
	
			}
	
			else
	
			{
		
				PQclear(res);
		
				PQfinish(conn);
		
				return 0;
	
			}
	
		}
	
return 0;

}