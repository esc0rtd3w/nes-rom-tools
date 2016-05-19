#include <cstdlib>
#include <iostream>

using namespace std;

char oldrom[255];
char exprom[255];

int main()
{
    unsigned long int oldrom_add=0;
    unsigned long int exprom_add=0;
    int PRG_banks;
    int CHR_banks;
    int copy_PRG_banks;
    int copy_CHR_banks;
    int original_PRG;
    int original_CHR;
    char readbyte;
    char do_copy_PRG_banks=0;
    char do_copy_CHR_banks=0;
    unsigned char mapper;
    cout<<"Nflate v1.0. (c) 2007 KingMike.\n";
    cout<<"Original NES ROM to expand:";
    //cin>>oldrom;
    int x=0;
    readbyte=0;
    while(readbyte!='\n')
    {
        readbyte=cin.get();
        oldrom[x++]=readbyte;
    }
    oldrom[x-1]='\0';
    //cout<<oldrom;
    cout<<"Save expanded ROM as:";
    //cin>>exprom;
    x=0;
    readbyte=0;
    while(readbyte!='\n')
    {
        readbyte=cin.get();
        exprom[x++]=readbyte;
    }
    exprom[x-1]='\0';
    //cout<<exprom;
    cout<<"Increase PRG ROM? (0=No, 1=Yes):";
    cin>>readbyte;
    //cout<<"["<<readbyte<<"]\n";
    if(readbyte=='1')
      do_copy_PRG_banks=1;
    readbyte=0;
    cout<<"Increase CHR ROM? (0=No, 1=Yes):";
    cin>>readbyte;
    //cout<<"["<<readbyte<<"]\n";
    if(readbyte=='1')
      do_copy_CHR_banks=1;
    //cout<<(int)do_copy_PRG_banks<<" "<<(int)do_copy_CHR_banks<<"\n";
    FILE *old=fopen(oldrom,"rb");
    if(old==NULL)
    {
        cout<<"Couldn't find the file \""<<oldrom<<"\".\n";
        system("PAUSE");
        return EXIT_FAILURE;
    }
    FILE *exp=fopen(exprom,"wb");
    if(exp==NULL)
    {
        cout<<"Couldn't find the file \""<<exprom<<"\".\n";
        system("PAUSE");
        return EXIT_FAILURE;
    }
    fseek(old,4,SEEK_SET);
    readbyte=fgetc(old);
    PRG_banks=readbyte;
    original_PRG=PRG_banks; //preserve original number of PRG banks
    copy_PRG_banks=do_copy_PRG_banks*PRG_banks; //going to double the PRG size.
    fseek(old,5,SEEK_SET);
    readbyte=fgetc(old);
    CHR_banks=readbyte;
    original_CHR=CHR_banks;   //preserve original number of CHR banks
    copy_CHR_banks=do_copy_CHR_banks*CHR_banks; //going to double the CHR size?
    fseek(old,6,SEEK_SET);
    readbyte=fgetc(old);
    mapper=(readbyte>>4);
    fseek(old,7,SEEK_SET);
    readbyte=fgetc(old);
    mapper=(readbyte&0xF0)+ mapper;
    //cout<<"Mapper "<<(int)mapper<<".:\n";
    if(mapper==0x13)      //mapper 19 (Namcot 106)
    {
        cout<<"iNES mapper 19 (Namcot 106) detected.\n";
        for(int x=0;x<16;x++)//copy the header.
        {
            fseek(old,oldrom_add,SEEK_SET);
            readbyte=fgetc(old);
            oldrom_add++;
            fseek(exp,exprom_add,SEEK_SET);
            fputc(readbyte,exp);
            exprom_add++;
        }
        cout<<"Copied the header.\n";
        fseek(exp,4,SEEK_SET);             //Update number of PRG and CHR banks in header.
        fputc((char)PRG_banks+(do_copy_PRG_banks*PRG_banks),exp);
        fseek(exp,5,SEEK_SET);
        fputc((char)CHR_banks+(do_copy_CHR_banks*CHR_banks),exp);
        fseek(exp,exprom_add,SEEK_SET);
        while(copy_PRG_banks>0)
        {
            for(int x=16384;x>0;x--)
            {
                fputc((unsigned char)0xFF,exp);
                exprom_add++;
            }
            copy_PRG_banks--;
        }
        cout<<"Added extra PRG banks.\n";
        while(PRG_banks>0)  //copy all 16KB of PRG
        {
            for(int x=16384;x>0;x--)
            {
                fseek(old,oldrom_add,SEEK_SET);
                readbyte=fgetc(old);
                oldrom_add++;
                fseek(exp,exprom_add,SEEK_SET);
                fputc(readbyte,exp);
                exprom_add++;
            }
            PRG_banks--;
        }
        cout<<"Copied all the PRG banks\n";
        while(CHR_banks>0)  //copy all but the last 16KB of PRG
        {
            for(int x=8192;x>0;x--)
            {
                fseek(old,oldrom_add,SEEK_SET);
                readbyte=fgetc(old);
                oldrom_add++;
                fseek(exp,exprom_add,SEEK_SET);
                fputc(readbyte,exp);
                exprom_add++;
            }
            CHR_banks--;
        }
        cout<<"Copied the CHR banks.\n";
        while(copy_CHR_banks>0)
        {
            for(int x=8192;x>0;x--)
            {
                fseek(exp,exprom_add,SEEK_SET);
                fputc((char)0,exp);
                exprom_add++;
            }
            copy_CHR_banks--;
        }
        if(do_copy_CHR_banks==1)   
           cout<<"Doubled the CHR banks.\n";        
    }
    else if((mapper==1 && copy_PRG_banks>=16) || mapper==82)  //Expanding MMC1 to > 256KB, or some Taito mapper.
    {
        if(mapper==1)
            cout<<"Detected Nintendo MMC1 expansion to over 256KB PRG.\n";
        if(mapper==82)
            cout<<"Detected iNES mapper #82.\n";
        for(int x=0;x<16;x++)//copy the header.
        {
            fseek(old,oldrom_add,SEEK_SET);
            readbyte=fgetc(old);
            oldrom_add++;
            fseek(exp,exprom_add,SEEK_SET);
            fputc(readbyte,exp);
            exprom_add++;
        }
        cout<<"Copied the header.\n";
        fseek(exp,4,SEEK_SET);             //Update number of PRG and CHR banks in header.
        fputc((char)PRG_banks+(do_copy_PRG_banks*PRG_banks),exp);
        fseek(exp,5,SEEK_SET);
        fputc((char)CHR_banks+(do_copy_CHR_banks*CHR_banks),exp);
        fseek(exp,exprom_add,SEEK_SET);
        while(PRG_banks>0)  //copy all RPG
        {
            for(int x=16384;x>0;x--)
            {
                fseek(old,oldrom_add,SEEK_SET);
                readbyte=fgetc(old);
                oldrom_add++;
                fseek(exp,exprom_add,SEEK_SET);
                fputc(readbyte,exp);
                exprom_add++;
            }
            PRG_banks--;
        }
        cout<<"Copied all the PRG banks\n";
        while(copy_PRG_banks>1)
        {
            for(int x=16384;x>0;x--)
            {
                fputc((unsigned char)0xFF,exp);
                exprom_add++;
            }
            copy_PRG_banks--;
        }
        cout<<"Added extra PRG banks.\n";
        cout<<"Replicating last PRG bank.";
        fseek(old,((original_PRG-1)*16384)+16,SEEK_SET);
        for(int x=16384; x>0; x--)
        {
            readbyte=fgetc(old);
            fseek(exp,exprom_add,SEEK_SET);
            fputc(readbyte,exp);
            exprom_add++;
        }
        while(CHR_banks>0)  //copy all but the last 16KB of PRG
        {
            for(int x=8192;x>0;x--)
            {
                fseek(old,oldrom_add,SEEK_SET);
                readbyte=fgetc(old);
                oldrom_add++;
                fseek(exp,exprom_add,SEEK_SET);
                fputc(readbyte,exp);
                exprom_add++;
            }
            CHR_banks--;
        }
        cout<<"Copied the CHR banks.\n";
        while(copy_CHR_banks>0)
        {
            for(int x=8192;x>0;x--)
            {
                fseek(exp,exprom_add,SEEK_SET);
                fputc((char)0,exp);
                exprom_add++;
            }
            copy_CHR_banks--;
        }
        if(do_copy_CHR_banks==1)   
           cout<<"Doubled the CHR banks.\n";
    }
    //if not a mapper with special enhancement
    else
    {
        for(int x=0;x<16;x++)//copy the header.
        {
            fseek(old,oldrom_add,SEEK_SET);
            readbyte=fgetc(old);
            oldrom_add++;
            fseek(exp,exprom_add,SEEK_SET);
            fputc(readbyte,exp);
            exprom_add++;
        }
        cout<<"Copied the header.\n";
        fseek(exp,4,SEEK_SET);
        fputc((char)PRG_banks+(do_copy_PRG_banks*PRG_banks),exp);
        fseek(exp,5,SEEK_SET);
        fputc((char)CHR_banks+(do_copy_CHR_banks*CHR_banks),exp);
        while(PRG_banks>1)  //copy all but the last 16KB of PRG
        {
            for(int x=16384;x>0;x--)
            {
                fseek(old,oldrom_add,SEEK_SET);
                readbyte=fgetc(old);
                oldrom_add++;
                fseek(exp,exprom_add,SEEK_SET);
                fputc(readbyte,exp);
                exprom_add++;
            }
            PRG_banks--;
        }
        cout<<"Copied all but the last PRG bank\n";
        while(copy_PRG_banks>0)
        {
            for(int x=16384;x>0;x--)
            {
                fseek(exp,exprom_add,SEEK_SET);
                fputc((char)0,exp);
                exprom_add++;
            }
            copy_PRG_banks--;
        }
        if(do_copy_PRG_banks==1)
            cout<<"Doubled the PRG banks\n";
        //copy the last 16KB of PRG
        for(int x=16384;x>0;x--)
        {
            fseek(old,oldrom_add,SEEK_SET);
            readbyte=fgetc(old);
            oldrom_add++;
            fseek(exp,exprom_add,SEEK_SET);
            fputc(readbyte,exp);
            exprom_add++;
        }
        cout<<"Copied the last PRG bank.\n";
        while(CHR_banks>0)  //copy all but the last 16KB of PRG
        {
            for(int x=8192;x>0;x--)
            {
                fseek(old,oldrom_add,SEEK_SET);
                readbyte=fgetc(old);
                oldrom_add++;
                fseek(exp,exprom_add,SEEK_SET);
                fputc(readbyte,exp);
                exprom_add++;
            }
            CHR_banks--;
        }
        cout<<"Copied the CHR banks.\n";
        while(copy_CHR_banks>0)
        {
            for(int x=8192;x>0;x--)
            {
                fseek(exp,exprom_add,SEEK_SET);
                fputc((char)0,exp);
                exprom_add++;
            }
            copy_CHR_banks--;
        }
        if(do_copy_CHR_banks==1)   
           cout<<"Doubled the CHR banks.\n";
    }//end of standard NES mapper
    system("PAUSE");
    return EXIT_SUCCESS;
}
