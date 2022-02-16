#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <arpa/inet.h>

#define SIZE 1024

void write_file(int sockfd)
{
    int n;
    FILE *fp;
    char *filename = "file2.txt";
    char buffer[SIZE];

    fp = fopen(filename, "w");
    if(fp==NULL)
    {
        perror("[-]Error in creating file.");
        exit(1);
    }
    while(1)
    {
        n = recv(sockfd, buffer, SIZE, 0);
        if(n<=0)
        {
            break;
            return;
        }
        fprintf(fp, "%s", buffer);
        bzero(buffer, SIZE);
    }
    return;

}


#include <signal.h>


#define RUNNING_DIR "/tmp"
#define LOCK_FILE   "exampled.lock"
#define LOG_FILE    "exampled.log"

void log_message(filename,message)
char *filename;
char *message;
{
FILE *logfile;
    logfile=fopen(filename,"a");
    if(!logfile) return;
    fprintf(logfile,"%s\n",message);
    fclose(logfile);
}

void signal_handler(sig)
int sig;
{
    switch(sig) {
    case SIGHUP:
        log_message(LOG_FILE,"hangup signal catched");
        break;
    case SIGTERM:
        log_message(LOG_FILE,"terminate signal catched");
        exit(0);
        break;
    }
}

void daemonize()
{
int i,lfp;
char str[10];
	if(getppid()==1) return; //Si e pid = 1 c'est déjà un daemon donc on sort
	i=fork(); //Création du fils sinon
	if (i<0) exit(1); //Si le pid <0 on a une erreur
	if (i>0) exit(0); //Si le pid >0 le père n'est plus nécessaire donc on sort
	//On continu pour le fils daemon
	setsid(); //Création nouvelle session
	for (i=getdtablesize();i>=0;--i) close(i); //On ferme tout les descripteurs
	i=open("/dev/null",O_RDWR); dup(i); dup(i); //Redirige stdin/stdout/stdrr à null
	umask(027); //On attribut les nouvelles permissions au fichier créé
	chdir(RUNNING_DIR); //On change le dossier dans lequel on travaille
	lfp=open(LOCK_FILE,O_RDWR|O_CREAT,0640);
	if (lfp<0) exit(1); //Si le nombre de fichier < 0 on ne peut rien ouvrir
	if (lockf(lfp,F_TLOCK,0)<0) exit(0); //Si le nombre de fichier < 0 on ne peut rien verouiller
	//On continu lors du premier appel
	sprintf(str,"%d\n",getpid());
	write(lfp,str,strlen(str)); //Enregistrement du pid pour vérouiller le fichier
	signal(SIGCHLD,SIG_IGN); //Permet d'ignorer le fils
	signal(SIGTSTP,SIG_IGN); //Permet d'ignorer les signaux de mise en pause, des choses entrantes et sortantes
	signal(SIGTTOU,SIG_IGN);
	signal(SIGTTIN,SIG_IGN);
	signal(SIGHUP,signal_handler); //Permet d'attraper un signal
	signal(SIGTERM,signal_handler); //Permet de tuer le processus
}


int main ()
{
    daemonize();

    char *ip = "127.0.0.1";
    int port = 54545;
    int e;

    int sockfd, new_sock;
    struct sockaddr_in server_addr, new_addr;
    socklen_t addr_size;
    char buffer[SIZE];

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd<0)
    {
       perror("[-]Error in socket");
       exit(1);
    }
    printf("[+]Server socket created. \n");

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = inet_addr(ip);

    e = bind(sockfd,(struct sockaddr*)&server_addr, sizeof(server_addr));
    if(e<0)
    {
        perror("[-]Error in Binding");
        exit(1);
    }
    printf("[+]Binding Successfull.\n");

    e = listen(sockfd, 10);
    if(e==0)
    {
        printf("[+]Listening...\n");
    }    
    else 
    {
        perror("[-]Error in Binding");
        exit(1);
    }
    
    while(1)
    {
        addr_size = sizeof(new_addr);
        new_sock = accept(sockfd,(struct sockaddr*)&new_addr, &addr_size);

        write_file(new_sock);
        printf("[+]Data written in the text file\n");
    }
}
