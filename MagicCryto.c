// Inclusion of libraries 
#include <stdio.h>
#include <string.h>

// Declartion of functions created and used in this program. Some are useless and for de-bugging. 
// Most functions are used. Ones for debugging and testing are: writing and check. 

//used for creating the .crp or .txt files 
int creating(FILE** fp, char file[128]);

//removes the last character of a given array. I used this fucntion to remove the '\n'
//charcter from the end of the stdin given input 
void removeLast(char array[]);

//used to add text to a file, mainly used to test my program by adding text to a .txt and then encrypting it 
int writing(FILE** fIn, char file[]);

//adds .txt to the end of a given array 
void addTXT(char array[]);

//adds .crp to the end of a given array 
void addCRP(char array[]);\

//encrypts a given .txt file by creating the appropriately named .crp file and storing the encrypted text
void encrypt(FILE** fIn, FILE** fOut, char fileTxt[], char fileCrp[]);

//used to check if the end of the array ended in '\n'. past debugging, not used. 
int check(char array[]);

//decrypts a given .crp file by creating the appropriately named .txt file and storing the encrypted text
void decrypt(FILE** fIn, FILE** fOut, char fileTxt[], char fileCrp[]);



int main(){

    FILE *fp;
    FILE *file;
    char strings[128];
    char nullChar = '\0';
    char control;
    int counter = 0;
    int count = 0;
    int check;

    fgets(strings, 128, stdin);
    
    char* token;
    char files[6][128];
    token = strtok(strings," ");

    for(int j =0; j<6; j++)
    {
        for(int i=0;i<128;i++)
        {
            files[j][i] = nullChar;
        }
    }


    while(token)
    {
        strcpy(files[counter], token); 
        //printf("\nThe token is %s and the file in %d registor is %s \n", token, counter, files[counter]);
        token = strtok(NULL, " ");
        counter += 1;
    }

    //printf("%d", counter);

    for(int i=0;i<20;i++)
    {
        //printf("\n%c", files[counter-1][i]);
        if(files[counter-1][i] == nullChar)
        {
            break;
        }
        count += 1;
    }

    char fileTxt[count+1];
    char fileCrp[count+1];

    strcpy(fileTxt, "");
    strcpy(fileCrp, "");

    for(int i=0; i<count+1;i++)
    {
        fileTxt[i] = files[counter-1][i];
        fileCrp[i] = files[counter-1][i];
        //printf("\n%c", filename[i]);
    }

    removeLast(fileTxt);
    addTXT(fileTxt);

    removeLast(fileCrp);
    addCRP(fileCrp);    

    fp = fopen(fileTxt, "r");
    if(fp == NULL)
    {

        //printf("\n%s", fileTxt);

        check = creating(&fp, fileTxt);

        if(check == -1)
        {
            printf("\nError creating file.");
            return -1;
        }

    }

    else 
    {
        //printf("\nthis working as should");
    }
    fclose(fp);




    file = fopen(fileCrp, "r");
    if(file == NULL)
    {


        //printf("\n%s", fileCrp);

        check = creating(&file, fileCrp);

        if(check == -1)
        {
            printf("\nError creating file.");
            return -1;
        }

    }
    fclose(file);
    

    /*
    check = writing(&fp, fileTxt);

    if(check == -1)
    {
        printf("\nError opening file.");
        return -1;
    }
    */
    

    //char Testfile[16] = "Testfile.txt";

    



    if(files[0][0] ==  '-' && files[0][1] == 'D')
    {
        //printf("\nWe at least got here");
        decrypt(&fp, &file, fileTxt, fileCrp);
    }

    else
    {
        encrypt(&fp, &file, fileTxt, fileCrp);
    }


    fclose(fp);
    fclose(file);



    return 0;
}






int creating(FILE** fp, char file[])
{

    *fp = fopen(file, "w");

    if(*fp == NULL)
    {
        return -1;
    }

    else
    {
        //printf("\nIt opened!!");
        fclose(*fp);
        return 0;
    }

}



int writing(FILE** fp, char file[])
{

    *fp = fopen(file, "a");

    if(*fp == NULL)
    {
        return -1;
    }

    fprintf(*fp, "Hello There how are you?\nMy name is Sean Clarke.\tI like software!\n");

    fclose(*fp);

    return 0;

}



void removeLast(char array[])
{
    int length=0;
    length = strlen(array);
    //printf("\nThis is%ca test", array[length-1]);
    array[length-1] = '\0';
    
    return;
}

void addCRP(char array[])
{
    for(int i=0;i<128;i++)
    {

        if(array[i] == '.' || array[i] == '\0' || array[i] == '\n')
        {

            array[i] = '.';
            array[i+1] = 'c';
            array[i+2] = 'r';
            array[i+3] = 'p';
            array[i+4] = '\0';
            break;
        }
    }

    return;
}

void addTXT(char array[])
{
    for(int i=0;i<128;i++)
    {

        if(array[i] == '.' || array[i] == '\0' || array[i] == '\n')
        {

            array[i] = '.';
            array[i+1] = 't';
            array[i+2] = 'x';
            array[i+3] = 't';
            array[i+4] = '\0';
            break;
        }
    }

    return;
}

void encrypt(FILE** fIn, FILE** fOut, char fileTxt[], char fileCrp[])
{

    *fIn = fopen(fileTxt, "r");
    *fOut = fopen(fileCrp, "w");

    char fileLine[120] = "\0";
    int type;
    int i=0;
    int outChar = 0; 
    int fileIn[255] = {0}; 



    //printf("\n%s", fileLine);

    
    while(!feof(*fIn))
    {

        strcpy(fileLine, "");

        fgets(fileLine, 120, *fIn);
    
        //printf("\n%s", fileLine);

        if(fileLine == "")
        {
            break;
        }

        else if(fileLine == "\n")
        {
            break;
        }

        else if(fileLine == NULL)
        {
            break;
        }

        else if(strlen(fileLine) == 0)
        {
            break;
        }


        for(int j=0; j<122; j++)
        {
            fileIn[j] = fileLine[j];
            //printf("\n %d , %c", fileIn[j], fileLine[j]);

            if(fileLine[j] == '\t')
            {
                fprintf(*fOut, "TT");
                //printf("Yup, we found something");
            }

            else if(fileLine[j] == '\n')
            {
                fprintf(*fOut, "\n");
                //printf("Yup, we found something with a new space");
                break;
            }

            else
            {
                outChar = fileIn[j] - 16;
                if(outChar < 32)
                {
                    outChar = (outChar - 32) + 144;
                    fprintf(*fOut, "%X", outChar);
                }

                else if(outChar > 127)
                {
                    break;
                }

                else
                {
                    fprintf(*fOut, "%X", outChar);
                }

            }

        }
    

        //return; 

    }

    fclose(*fIn);
    fclose(*fOut);



    return;
}



int check(char array[])
{
    int length=0;
    length = strlen(array);
    //printf("\nThis is%ca test \nand This is%canother test", array[length], array[length-1]);

    if(array[length] == '\n')
    {
        return 1;
    }
    else
    {
        return 0;
    }
}




void decrypt(FILE** fIn, FILE** fOut, char fileTxt[], char fileCrp[])
{

    *fIn = fopen(fileCrp, "r");
    *fOut = fopen(fileTxt, "w");

    

    char fileLine[255] = "\0";
    int type;
    int i=0;
    int outChar = 0; 
    int fileIn[255] = {0}; 



    //printf("\n%s", fileLine);

    
    while(!feof(*fIn))
    {

        

        strcpy(fileLine, "");

        fgets(fileLine, 255, *fIn);
    
        //printf("\n%s", fileLine);
        

        if(fileLine == "")
        {
            break;
        }

        else if(fileLine == "\n")
        {
            break;
        }

        else if(fileLine == NULL)
        {
            break;
        }

        else if(strlen(fileLine) == 0)
        {
            break;
        }

        

        for(int j=0; j<255; j += 2)
        {

            //printf("\nWe are getting here");
            if(fileLine[j] == 'A')
            {
                fileIn[j] = 10; 
            }

            else if(fileLine[j] == 'B')
            {
                fileIn[j] = 11; 
            }
        
            else if(fileLine[j] == 'C')
            {
                fileIn[j] = 12; 
            }

            else if(fileLine[j] == 'D')
            {
                fileIn[j] = 13; 
            }

            else if(fileLine[j] == 'E')
            {
                fileIn[j] = 14; 
            }

            else if(fileLine[j] == 'F')
            {
                fileIn[j] = 15; 
            }

            else
            {
                fileIn[j] = fileLine[j];
                fileIn[j] = fileIn[j] - 48;
            }


            if(fileLine[j+1] == 'A')
            {
                fileIn[j+1] = 10; 
            }

            else if(fileLine[j+1] == 'B')
            {
                fileIn[j+1] = 11; 
            }
        
            else if(fileLine[j+1] == 'C')
            {
                fileIn[j+1] = 12; 
            }

            else if(fileLine[j+1] == 'D')
            {
                fileIn[j+1] = 13; 
            }

            else if(fileLine[j+1] == 'E')
            {
                fileIn[j+1] = 14; 
            }

            else if(fileLine[j+1] == 'F')
            {
                fileIn[j+1] = 15; 
            }

            else
            {
                fileIn[j+1] = fileLine[j+1];
                fileIn[j+1] = fileIn[j+1] - 48;
            }

            //printf("\n %d , %c", fileIn[j], fileLine[j]);
            //printf("\n %d , %c", fileIn[j+1], fileLine[j+1]);
            

            if(fileLine[j] == 'T' && fileLine[j+1] == 'T')
            {
                fprintf(*fOut, "\t");
                //printf("Yup, we found something");
            }

            else if(fileLine[j] == '\n' || fileLine[j+1] == '\n')
            {
                fprintf(*fOut, "\n");
                //printf("Yup, we found something with a new space");
                break;
            }

            else
            {

                outChar = fileIn[j] * 16;
                outChar = outChar + fileIn[j+1];
                outChar = outChar + 16;  

                if(outChar > 127)
                {
                    outChar = (outChar - 144) + 32;
                    fprintf(*fOut, "%c", outChar);
                }

                else if(outChar < 0)
                {
                    break;
                }

                else
                {
                    fprintf(*fOut, "%c", outChar);
                }

                //printf("%c", outChar);

            }

        }
    

        //return; 

    }

    fclose(*fIn);
    fclose(*fOut);



    return;
}
