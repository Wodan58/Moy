/*
 *  module  : japilib.c
 *  version : 1.2
 *  date    : 04/27/21
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <time.h>
#include <sys/stat.h>
#include "joy.h"

#define MAXBUF		256
#define MAXPATH		1024
#define MAXLINE		4096

/* function imported from fileselect.c */
extern char *__fileselect(int, char *, char *, char *);

/* function imported from imageio.c */
extern int __read_image(FILE *, char **, char **, char **, int *, int *);
extern int __write_image(FILE *, char *, char *, char *, int, int, int);

#ifdef __GNUC__
#include <unistd.h>
#include <netinet/in.h>
#include <netdb.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <netinet/tcp.h>
#endif

#ifdef  _MSC_VER
#include <process.h>
#include <direct.h>
#include <winsock.h>
#endif

#ifndef TCP_NODELAY
#define TCP_NODELAY	0x01
#endif

#include "japi_p.h"
#include "japi.h"
#if 0
#include "japiserver2.h"
#endif

#ifndef MAXPATH
#define MAXPATH		1024
#endif

#define DUMMYOBJ	1

/* Compiler Settings  */
#ifdef _MSC_VER
#define getdtablesize() 0
#endif

#ifdef __GNUC__
#define SOCKET		int
#endif

#define LOCALHOST	"localhost"

/* Integer 4 Byte */
#define int int
#define varint int *
#define intarr int *
#define varintarr int *

/* Strings */
#define string char *
#define retstr char *

/* Boolean 4 Byte */
#define bool int

#define MAXNAMEDCOLORS	17
static unsigned char cga_color[MAXNAMEDCOLORS][3] = {
    {0, 0, 0},        /* black        */
    {255, 255, 255},  /* white        */
    {255, 0, 0},      /* red          */
    {0, 255, 0},      /* green        */
    {0, 0, 255},      /* blue         */
    {0, 255, 255},    /* cyan         */
    {255, 0, 255},    /* magenta      */
    {255, 255, 0},    /* yellow       */
    {255, 127, 0},    /* orange       */
    {127, 255, 0},    /* green-yellow */
    {0, 255, 127},    /* green-cyan   */
    {0, 127, 255},    /* blue-cyan    */
    {127, 0, 255},    /* blue-magenta */
    {255, 0, 127},    /* red-magenta  */
    {64, 64, 64},     /* dark-gray    */
    {192, 192, 192},  /* light-gray   */
    {128, 128, 128}}; /* gray         */

static SOCKET commandstream = 0, actionstream = 0, httpsock = 0;
static int SWAP = 0;
static int port = JAPI_PORT;
static int debuglevel = 0;
static char buf[MAXPATH];
static char *bufptr = buf;

static int write_server();
static int socket_read();
static char *swap_4byte();
static void send_int();
static void send_string();

#ifdef _MSC_VER
static int init_WsockDll(void)
{
    int err;
    WORD wVersionRequested; /* Consist Version Nr. of Wsock32.dll */
    WSADATA wsaData;        /* Info about Sockets */

    wVersionRequested = MAKEWORD(1, 1);

    err = WSAStartup(wVersionRequested, &wsaData);
    if (err != 0)
	return err;

    if (LOBYTE(wsaData.wVersion) != 1 || HIBYTE(wsaData.wVersion) != 1) {
	WSACleanup();
	return -1;
    }
    return 0;
}

static int init_sock() { return init_WsockDll(); }

#ifdef bcc32
static void msleep(int msecs) { _sleep(msecs / 1000); }
#else
static void msleep(int msecs) { _sleep(msecs); }
#endif
#endif

#ifdef __GNUC__
static int init_sock() { return 0; }
static void msleep(int msecs) { usleep(1000 * msecs); }
#endif

#ifndef _MSC_VER
#define _P_WAIT		0
#define _P_NOWAIT	1
#define PATHSEP		':'
#define DIRSEP		"/"

#if 0
char *__isexec(char *fname, char *fpath, char *retname)
{
    char *ptr;
    struct stat statbuf;

    ptr = retname;
    while (strlen(fpath) > 0) {
	while (*fpath != PATHSEP && *fpath != 0)
	    *ptr++ = *fpath++;
	*ptr = 0;
	ptr = retname;
	fpath++;
	strcat(retname, DIRSEP);
	strcat(retname, fname);
	if (!stat(retname, &statbuf))
	    if (statbuf.st_mode & S_IEXEC)
		return retname;
    }
    return NULL;
}

short spawnvp(int mode, char *file, char **args)
{
    int status = 0;
    char retname[MAXBUF];

    if (!__isexec(file, getenv("PATH"), retname))
	return -1;
    else {
	if (fork() == 0) {
	    execv(retname, args);
	    _exit(-1);
	}
	if (mode == _P_WAIT)
	    wait(&status);
	return status;
    }
}
#endif

static int closesocket(SOCKET s) { return (close(s)); }

#endif

#if 0
static int start_kernel()
{
    char *args[10];

#ifdef _WIN32
#define JVM "javaw"
#else
#define JVM "java"
#endif

    args[0] = JVM;
    args[1] = "-cp";
    args[2] = "./JAPI.jar";
// Main class is now:
    args[3] = "japi.Japi2";
    args[4] = malloc(10);
    sprintf(args[4], "%d", port);
    args[5] = NULL;

    if (spawnvp(_P_NOWAIT, JVM, args) == -1) {
#ifdef unix
	system("xmessage \"No Java Runtime Environment found ...\" ");
#else
	system("msg * /time:0 \"No Java Runtime Environment found ...\" ");
#endif
	printf("No Java Runtime Environment found ...\n");
	return J_FALSE;
    }
    if (debuglevel > 0)
	printf(" found JAVA\n");
    return J_TRUE;
}
#endif

static bool establish_connect(char *hostname)
{
    int length;
    unsigned int type, magic;
    struct sockaddr_in adresse;

    if (debuglevel)
	printf("Commandsock %d\n", commandstream);
    if (debuglevel)
	printf("Actionsock %d\n", actionstream);

    type = 1;
    setsockopt(commandstream, IPPROTO_TCP, TCP_NODELAY, (char *)&type,
	       sizeof(type));
    setsockopt(actionstream, IPPROTO_TCP, TCP_NODELAY, (char *)&type,
	       sizeof(type));

    /* magic number empfangen, test ob SWAP noetig */
    if (socket_read(commandstream, &magic, sizeof(magic)) != sizeof(magic))
	return J_FALSE;

    if (debuglevel)
	printf("Magic Number = %d\n", magic);
    if (magic == 1234)
	SWAP = 0;
    else {
	swap_4byte((char *)&magic, 1);
	if (magic == 1234)
	    SWAP = 1;
	else
	    return J_FALSE;
    }

    if (debuglevel) {
	if (SWAP)
	    printf("Unterschiedliche Binaer Formate -> Swapping ein\n");
	else
	    printf("No Swapping\n");
    }

    /* debuglevel senden */
    send_int(abs(debuglevel));

    /* HTTP Socket */
    send_string(hostname);

    if ((httpsock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	return J_FALSE;
    adresse.sin_family = AF_INET;
    adresse.sin_addr.s_addr = INADDR_ANY;
    adresse.sin_port = 0;
    if (bind(httpsock, (struct sockaddr *)&adresse, sizeof(adresse)) != 0)
	return J_FALSE;
    length = sizeof(adresse);
    if (getsockname(httpsock, (struct sockaddr *)&adresse, &length))
	return J_FALSE;
    send_int((int)ntohs(adresse.sin_port));
    listen(httpsock, 10);
    return J_TRUE;
}

bool japi_start()
{
    char hostname[MAXPATH], path[MAXPATH];
    struct sockaddr_in adresse;
    struct hostent *hp;

    srand(time(NULL));

    if (init_sock() != 0)
	return J_FALSE;

    adresse.sin_family = AF_INET;
    if ((hp = gethostbyname(LOCALHOST)) == NULL) {
	gethostname(hostname, MAXPATH);
	if ((hp = gethostbyname(hostname)) == NULL)
	    return J_FALSE;
    }
    memcpy(&adresse.sin_addr, hp->h_addr, hp->h_length);
    adresse.sin_port = htons(port);

    if ((commandstream = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	return J_FALSE;
    if (connect(commandstream, (struct sockaddr *)&adresse, sizeof(adresse)) <
		0) {
	return (J_FALSE);
#if 0
    if (debuglevel)
      printf("can't connect to server -> starting new kernel\n");

    getcwd(path, MAXPATH);
    if (getenv("TMP") != NULL)
      chdir(getenv("TMP"));
    if (getenv("TEMP") != NULL)
      chdir(getenv("TEMP"));

    /* first in /tmp then in . */
    if (write_server() < 0) {
      chdir(path);
      if (write_server() < 0)
        return (J_FALSE);
    }
    if (!start_kernel())
      return (J_FALSE);
    chdir(path);

    do {
      msleep(1000);
      if (debuglevel)
        printf("trying to connect\n");

      closesocket(commandstream);
      if ((commandstream = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        return (J_FALSE);
    } while (connect(commandstream, (struct sockaddr *)&adresse,
                     sizeof(adresse)) < 0);
#endif
    }

    if ((actionstream = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	return J_FALSE;
    if (connect(actionstream, (struct sockaddr *)&adresse, sizeof(adresse)) < 0)
	return J_FALSE;

    /* unlink("JAPI.jar"); */
    if ((hp = gethostbyname(LOCALHOST)) == NULL) {
	gethostname(hostname, MAXPATH);
	return establish_connect(hostname);
    }

    return establish_connect(LOCALHOST);
}

bool japi_connect(string hostname)
{
    struct sockaddr_in adresse;
    struct hostent *hp;

    if (init_sock() != 0)
	return J_FALSE;

    adresse.sin_family = AF_INET;
    if ((hp = gethostbyname(hostname)) == 0)
	return J_FALSE;
    memcpy(&adresse.sin_addr, hp->h_addr, hp->h_length);
    adresse.sin_port = htons(port);

    if ((commandstream = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	return J_FALSE;
    if (connect(commandstream, (struct sockaddr *)&adresse,sizeof(adresse)) < 0)
	return J_FALSE;
    if ((actionstream = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	return J_FALSE;
    if (connect(actionstream, (struct sockaddr *)&adresse, sizeof(adresse)) < 0)
	return J_FALSE;
    return establish_connect(hostname);
}

static int readline(int s, char *line)
{
    int n = 0;
    char c = 0;

    while (c != 10) {
	socket_read(s, &c, 1);
	line[n++] = c;
    }
    line[n] = 0;
    return n;
}

static int writeline(int s, char *buf)
{
    return send(s, buf, strlen(buf), 0);
}

static int httpsend()
{
    int kernel;
    char line[MAXLINE], tmp[MAXBUF], filename[MAXPATH];
    int i, leng, nread;
    FILE *fd;

    if ((kernel = accept(httpsock, 0, 0)) == -1)
	return -1;
    readline(kernel, line);
    sscanf(line, "%s %s", tmp, filename);
    leng = strlen(line);
    for (i = 0; i < leng; i++)
	if (line[i] == ']')
	    break;
    memcpy(filename, &(line[i + 1]), strlen(line) - i);
    *strrchr(filename, '[') = 0;
    while (*line != '\r' && line[1] != '\n')
	readline(kernel, line);

    if ((fd = fopen(filename, "rb")) == NULL) {
	writeline(kernel, "HTTP/1.1 404 not found\r\n");
	writeline(kernel, "\r\n");
    } else {
	writeline(kernel, "HTTP/1.1 200 OK\r\n");
	/* writeline(kernel,"Content-Type: image/gif\r\n"); */
	writeline(kernel, "\r\n");
	while ((nread = fread(line, 1, MAXLINE, fd)) > 0)
	    send(kernel, line, nread, 0);
	fclose(fd);
    }
    closesocket(kernel);
    return 1;
}

static char *tmpname(char *title)
{
    static long tmpval = 0;
    char tmpstr[MAXPATH];

    sprintf(tmpstr, "[%ld]%s", ++tmpval, title);
    sprintf(&(title[strlen(title)]), "%s[%ld]", tmpstr, tmpval);
    return title;
}

/*                               TOOLS  */
static int get_message()
{
    fd_set fdset;
    struct timeval timeout;

    FD_ZERO(&fdset);
    FD_SET(actionstream, &fdset);
    timeout.tv_sec = 0;
    timeout.tv_usec = 0;
    if (select(sizeof(fdset) * 8, &fdset, NULL, NULL, &timeout) == 1)
	return 1;
    else
	return 0;
}

static int socket_read(int file_d, char *buf, int nbytes)
{
    int n_bytes_gelesen = 0, n;
    char *posbuf;

    while (n_bytes_gelesen < nbytes) {
	posbuf = (char *)(buf + n_bytes_gelesen);
#ifdef _MSC_VER
	n = recv(file_d, posbuf, nbytes - n_bytes_gelesen, 0);
#else
	n = read(file_d, posbuf, nbytes - n_bytes_gelesen);
#endif
	if (n > 0)
	    n_bytes_gelesen += n;
	else {
	    if (errno != EINTR)
		exit(-1);
	}
    }
    return n_bytes_gelesen;
}

static char *swap_4byte(char *buf, int size)
{
    char merk;
    register int i;

    for (i = 0; i < size; i += 4) {
	merk = buf[i];
	buf[i] = buf[i + 3];
	buf[i + 3] = merk;
	merk = buf[i + 1];
	buf[i + 1] = buf[i + 2];
	buf[i + 2] = merk;
    }
    return buf;
}

#if 0
static int write_server()
{
    FILE *fd;

    if ((fd = fopen("JAPI.jar", "wb")) == NULL)
	return -1;
    if (fwrite(JAPISERVER, 1, JAPISERVERLENGTH, fd) != JAPISERVERLENGTH)
	return -1;
    fclose(fd);
    return 1;
}
#endif

/*	         gepufferte  Sendefunktionen        */

static void add_string(char *s)
{
    int len = strlen(s) + 1;

    memcpy(bufptr, s, len);
    bufptr += len;
    bufptr[-1] = '\n';
}

static void add_int(int val)
{
    if (SWAP)
	swap_4byte((char *)&val, 1);
    memcpy(bufptr, &val, sizeof(val));
    bufptr += sizeof(val);
}

static void add_char(char c)
{
    memcpy(bufptr++, &c, 1);
}

static void send_buf()
{
    int i, gesendet, len = bufptr - buf;

    while ((gesendet = send(commandstream, buf, len, 0)) < len) {
	printf(
    "This is a serious E R R O R: sent %d Bytes, should have sent %d Bytes\n",
	gesendet, len);
	printf(
    "Please report this error to 'evol@uni-koblenz.de'\n, bytes to send are : "
	);
	for (i = 0; i < len; i++)
	    printf("%d ", (unsigned char)buf[i]);
	printf("\n");
    }
    bufptr = buf;
}

/*			elementare   Empfangsfunktionen               */

static int get_int(int fd)
{
    int obj;

    socket_read(fd, (char *)&obj, sizeof(obj));
    if (SWAP)
	swap_4byte((char *)&obj, 1);
    return obj;
}

static void get_string(int fd, char *s)
{
    int length;

    socket_read(fd, (char *)&length, sizeof(length));
    if (SWAP)
	swap_4byte((char *)&length, 1);
    if (length > 0)
	socket_read(fd, s, length);
    s[length] = 0;
}

/*			zusammengesetzte     Sende- und Empfangsfunktionen */

static void add_2int(int v1, int v2)
{
    add_int(v1);
    add_int(v2);
}

static void add_3int(int v1, int v2, int v3)
{
    add_2int(v1, v2);
    add_int(v3);
}

static void add_4int(int v1, int v2, int v3, int v4)
{
    add_2int(v1, v2);
    add_2int(v3, v4);
}

static void send_char(char c)
{
    add_char(c);
    send_buf();
}

static void send_string(char *s)
{
    add_string(s);
    send_buf();
}

static void send_int(int c)
{
    add_int(c);
    send_buf();
}

static void send_2int(int c, int o)
{
    add_2int(c, o);
    send_buf();
}

static void send_3int(int c, int o, int v)
{
    add_3int(c, o, v);
    send_buf();
}

static void send_2int_char(int c, int o, char s)
{
    add_2int(c, o);
    add_char(s);
    send_buf();
}

static void send_2int_string(int c, int o, char *s)
{
    add_2int(c, o);
    add_string(s);
    send_buf();
}

static void send_4int(int c, int o, int v1, int v2)
{
    add_4int(c, o, v1, v2);
    send_buf();
}

static void send_3int_string(int c, int o, int v, char *s)
{
    add_3int(c, o, v);
    add_string(s);
    send_buf();
}

static void send_4int_string(int c, int o, int v1, int v2, char *s)
{
    add_4int(c, o, v1, v2);
    add_string(s);
    send_buf();
}

static void send_5int(int c, int o, int v1, int v2, int v3)
{
    add_4int(c, o, v1, v2);
    add_int(v3);
    send_buf();
}

static void send_6int(int c, int o, int v1, int v2, int v3, int v4)
{
    add_3int(c, o, v1);
    send_3int(v2, v3, v4);
}

static void send_8int(int c, int o, int v1, int v2, int v3, int v4, int v5,
                      int v6)
{
    add_4int(c, o, v1, v2);
    send_4int(v3, v4, v5, v6);
}

static int send_2int_get_int(int c, int o)
{
    send_2int(c, o);
    return get_int(commandstream);
}

static void send_2int_get_string(int c, int o, char *s)
{
    send_2int(c, o);
    get_string(commandstream, s);
}

static void send_3int_get_string(int c, int o, int n, char *s)
{
    send_3int(c, o, n);
    get_string(commandstream, s);
}

static int send_3int_get_int(int c, int o, int v)
{
    send_3int(c, o, v);
    return get_int(commandstream);
}

static int send_2int_string_get_int(int c, int o, char *s)
{
    send_2int_string(c, o, s);
    return get_int(commandstream);
}

static void send_2int_3string_get_string(int c, int o, char *a, char *s,
                                         char *d, char *r)
{
    add_2int(c, o);
    add_string(a);
    add_string(s);
    add_string(d);
    send_buf();
    get_string(commandstream, r);
}

static int send_4int_get_int(int c, int o, int v1, int v2)
{
    send_4int(c, o, v1, v2);
    return get_int(commandstream);
}

static int send_5int_get_int(int c, int o, int v1, int v2, int v3)
{
    send_5int(c, o, v1, v2, v3);
    return get_int(commandstream);
}

static void send_intarray(int *v, int n)
{
    if (SWAP)
	swap_4byte((char *)v, n * sizeof(int));
    send(commandstream, (char *)v, n * sizeof(int), 0);
    if (SWAP)
	swap_4byte((char *)v, n * sizeof(int));
}

/* J A P I   Funktionen */

int japi_splitpane(int parent, int orientation, int init_position)
{
    return send_4int_get_int(JAPI_SPLITPANE, parent, orientation, init_position);
}

void japi_setsplitpaneleft(int sp, int component)
{
    send_3int(JAPI_SETSPLITPANELEFT, sp, component);
}

void japi_setsplitpaneright(int sp, int component)
{
    send_3int(JAPI_SETSPLITPANERIGHT, sp, component);
}

void japi_setport(int p)
{
    port = p;
}

void japi_setdebug(int level)
{
    debuglevel = level;
    if (commandstream != 0)
	send_3int(JAPI_DEBUG, DUMMYOBJ, abs(debuglevel));
}

int japi_frame(string title)
{
    if (!title || !*title)
	return send_2int_string_get_int(JAPI_FRAME, DUMMYOBJ,
			"JAPI (Java Application Programming Interface)");
    else
	return send_2int_string_get_int(JAPI_FRAME, DUMMYOBJ, title);
}

int japi_button(int parent, string title)
{
    return send_2int_string_get_int(JAPI_BUTTON, parent, title);
}

int japi_graphicbutton(int parent, string title)
{
    char fname[MAXPATH];

    sprintf(fname, "%s", title);
    send_2int_string(JAPI_GRAPHICBUTTON, parent, tmpname(fname));
    httpsend();
    return get_int(commandstream);
}

int japi_checkbox(int parent, string title)
{
    return send_2int_string_get_int(JAPI_CHECKBOX, parent, title);
}

int japi_label(int parent, string title)
{
    return send_2int_string_get_int(JAPI_LABEL, parent, title);
}

int japi_graphiclabel(int parent, string title)
{
    char fname[MAXPATH];

    sprintf(fname, "%s", title);
    send_2int_string(JAPI_GRAPHICLABEL, parent, tmpname(fname));
    httpsend();
    return get_int(commandstream);
}

int japi_canvas(int parent, int w, int h)
{
    return send_4int_get_int(JAPI_CANVAS, parent, w, h);
}

int japi_panel(int parent)
{
    return send_3int_get_int(JAPI_PANEL, parent, J_NONE);
}

int japi_borderpanel(int parent, int type)
{
    return send_3int_get_int(JAPI_PANEL, parent, type);
}

int japi_radiogroup(int parent)
{
    return send_2int_get_int(JAPI_RADIOGROUP, parent);
}

int japi_radiobutton(int parent, string title)
{
    return send_2int_string_get_int(JAPI_RADIOBUTTON, parent, title);
}

int japi_list(int parent, int rows)
{
    return send_3int_get_int(JAPI_LIST, parent, rows);
}

int japi_choice(int parent)
{
    return send_2int_get_int(JAPI_CHOICE, parent);
}

int japi_dialog(int parent, string title)
{
    return send_2int_string_get_int(JAPI_DIALOG, parent, title);
}

int japi_window(int parent)
{
    return send_2int_get_int(JAPI_WINDOW, parent);
}

int japi_popupmenu(int parent, string title)
{
    return send_2int_string_get_int(JAPI_POPMENU, parent, title);
}

int japi_scrollpane(int parent)
{
    return send_2int_get_int(JAPI_SCROLLPANE, parent);
}

int japi_hscrollbar(int parent)
{
    return send_2int_get_int(JAPI_HSCROLL, parent);
}

int japi_vscrollbar(int parent)
{
    return send_2int_get_int(JAPI_VSCROLL, parent);
}

int japi_line(int parent, int orient, int style, int len)
{
    return send_5int_get_int(JAPI_RULER, parent, orient, style, len);
}

int japi_printer(int frame)
{
    return send_2int_get_int(JAPI_PRINTER, frame);
}

int japi_image(int w, int h)
{
    return send_4int_get_int(JAPI_IMAGE, DUMMYOBJ, w, h);
}

string japi_filedialog(int parent, string title, string directory,
                       retstr filename)
{
    char path[MAXPATH];

    if (!filename) {
	filename = GC_malloc_atomic(MAXPATH);
	*filename = 0;
    }
    send_2int_3string_get_string(JAPI_FILEDIALOG, parent, getcwd(path, MAXPATH),
				 title, directory, filename);
    return filename;
}

string japi_fileselect(int frame, string title, string filter, retstr filename) {
    if (!filename) {
	filename = GC_malloc_atomic(MAXPATH);
	*filename = 0;
    }
    return __fileselect(frame, title, filename, filter);
}

int japi_messagebox(int parent, string title, string text)
{
    int len = strlen(text);

    send_3int_string(JAPI_MESSAGEBOX, parent, len, title);
    send(commandstream, text, len, 0);
    return get_int(commandstream);
}

int japi_alertbox(int parent, string title, string text, string ok)
{
    int len = strlen(text);

    send_3int_string(JAPI_ALERTBOX, parent, len, title);
    send_string(ok);
    send(commandstream, text, len, 0);
    return get_int(commandstream);
}

int japi_choicebox2(int parent, string title, string text, string ok1,
                    string ok2)
{
    int len = strlen(text);

    send_3int_string(JAPI_CHOICEBOX2, parent, len, title);
    send_string(ok1);
    send_string(ok2);
    send(commandstream, text, len, 0);
    return get_int(commandstream);
}

int japi_choicebox3(int parent, string title, string text, string ok1,
                    string ok2, string ok3)
{
    int len = strlen(text);

    send_3int_string(JAPI_CHOICEBOX3, parent, len, title);
    send_string(ok1);
    send_string(ok2);
    send_string(ok3);
    send(commandstream, text, len, 0);
    return get_int(commandstream);
}

int japi_progressbar(int parent, int o)
{
    return send_3int_get_int(JAPI_PROGRESSBAR, parent, o);
}

int japi_led(int parent, int f, int c)
{
    send_3int(JAPI_LED, parent, f);
    add_char(cga_color[c % MAXNAMEDCOLORS][0]);
    add_char(cga_color[c % MAXNAMEDCOLORS][1]);
    send_char(cga_color[c % MAXNAMEDCOLORS][2]);
    return get_int(commandstream);
}

int japi_sevensegment(int parent, int c)
{
    send_2int(JAPI_SEVENSEGMENT, parent);
    add_char(cga_color[c % MAXNAMEDCOLORS][0]);
    add_char(cga_color[c % MAXNAMEDCOLORS][1]);
    send_char(cga_color[c % MAXNAMEDCOLORS][2]);
    return get_int(commandstream);
}

int japi_meter(int parent, string t)
{
    return send_2int_string_get_int(JAPI_METER, parent, t);
}

void japi_additem(int parent, string title)
{
    send_2int_string(JAPI_ADDITEM, parent, title);
}

int japi_textfield(int parent, int col)
{
    return send_3int_get_int(JAPI_TEXTFIELD, parent, col);
}

int japi_textarea(int parent, int col, int row)
{
    return send_4int_get_int(JAPI_TEXTAREA, parent, row, col);
}

int japi_menubar(int frame)
{
    return send_2int_get_int(JAPI_MENUBAR, frame);
}

int japi_menu(int menubar, string title)
{
    return send_2int_string_get_int(JAPI_MENU, menubar, title);
}

int japi_helpmenu(int menubar, string title)
{
    return send_2int_string_get_int(JAPI_HELPMENU, menubar, title);
}

int japi_menuitem(int menu, string title)
{
    return send_2int_string_get_int(JAPI_MENUITEM, menu, title);
}

int japi_checkmenuitem(int menu, string title)
{
    return send_2int_string_get_int(JAPI_CHECKMENUITEM, menu, title);
}

void japi_pack(int obj)
{
    send_2int(JAPI_PACK, obj);
}

void japi_print(int obj)
{
    send_2int(JAPI_PRINT, obj);
}

void japi_playsoundfile(string filename)
{
    char fname[MAXPATH];

    sprintf(fname, "%s", filename);
    send_2int_string(JAPI_PLAYSOUNDFILE, DUMMYOBJ, tmpname(fname));
    httpsend();
}

void japi_play(int obj)
{
    send_2int(JAPI_PLAY, obj);
}

int japi_sound(string filename)
{
    char fname[MAXPATH];

    sprintf(fname, "%s", filename);
    send_2int_string(JAPI_SOUND, DUMMYOBJ, tmpname(fname));
    httpsend();
    return get_int(commandstream);
}

void japi_setfont(int obj, int font, int style, int size)
{
    send_5int(JAPI_SETFONT, obj, font, style, size);
}

void japi_setfontname(int obj, int font)
{
    send_3int(JAPI_SETFONTNAME, obj, font);
}

void japi_setfontsize(int obj, int size)
{
    send_3int(JAPI_SETFONTSIZE, obj, size);
}

void japi_setfontstyle(int obj, int size)
{
    send_3int(JAPI_SETFONTSTYLE, obj, size);
}

void japi_separator(int menu)
{
    send_2int(JAPI_SEPARATOR, menu);
}

void japi_disable(int obj)
{
    send_2int(JAPI_DISABLE, obj);
}

void japi_enable(int obj)
{
    send_2int(JAPI_ENABLE, obj);
}

bool japi_getstate(int obj)
{
    return send_2int_get_int(JAPI_GETSTATE, obj);
}

int japi_getrows(int obj)
{
    return send_2int_get_int(JAPI_GETROWS, obj);
}

int japi_getcolumns(int obj)
{
    return send_2int_get_int(JAPI_GETCOLUMNS, obj);
}

int japi_getselect(int obj)
{
    return send_2int_get_int(JAPI_GETSELECT, obj);
}

bool japi_isselect(int obj, int item)
{
    return send_3int_get_int(JAPI_ISSELECT, obj, item);
}

bool japi_isvisible(int obj)
{
    return send_2int_get_int(JAPI_ISVISIBLE, obj);
}

bool japi_isparent(int obj, int cont)
{
    return send_3int_get_int(JAPI_ISPARENT, obj, cont);
}

bool japi_isresizable(int obj)
{
    return send_2int_get_int(JAPI_ISRESIZABLE, obj);
}

void japi_select(int obj, int item)
{
    send_3int(JAPI_SELECT, obj, item);
}

void japi_deselect(int obj, int item)
{
    send_3int(JAPI_DESELECT, obj, item);
}

void japi_multiplemode(int obj, bool value)
{
    send_3int(JAPI_MULTIPLEMODE, obj, value);
}

void japi_insert(int parent, int pos, string title)
{
    send_3int_string(JAPI_INSERT, parent, pos, title);
}

void japi_remove(int obj, int item)
{
    send_3int(JAPI_REMOVE, obj, item);
}

void japi_removeitem(int obj, string item)
{
    send_2int_string(JAPI_REMOVEITEM, obj, item);
}

void japi_removeall(int obj)
{
    send_2int(JAPI_REMOVEALL, obj);
}

void japi_setstate(int obj, bool value)
{
    send_3int(JAPI_SETSTATE, obj, value);
}

void japi_setrows(int obj, int value)
{
    send_3int(JAPI_SETROWS, obj, value);
}

void japi_setcolumns(int obj, int value)
{
    send_3int(JAPI_SETCOLUMNS, obj, value);
}

void japi_seticon(int obj, int icon)
{
    send_3int(JAPI_SETICON, obj, icon);
}

void japi_setimage(int obj, int image)
{
    send_3int(JAPI_SETIMAGE, obj, image);
}

void japi_setvalue(int obj, int value)
{
    send_3int(JAPI_SETVALUE, obj, value);
}

void japi_setradiogroup(int obj, int rg)
{
    send_3int(JAPI_SETRADIOGROUP, obj, rg);
}

void japi_setunitinc(int obj, int value)
{
    send_3int(JAPI_SETUNITINC, obj, value);
}

void japi_setblockinc(int obj, int value)
{
    send_3int(JAPI_SETBLOCKINC, obj, value);
}

void japi_setmin(int obj, int value)
{
    send_3int(JAPI_SETMIN, obj, value);
}

void japi_setmax(int obj, int value)
{
    send_3int(JAPI_SETMAX, obj, value);
}

void japi_setdanger(int obj, int value)
{
    send_3int(JAPI_SETDANGER, obj, value);
}

void japi_setslidesize(int obj, int value)
{
    send_3int(JAPI_SETVISIBLE, obj, value);
}

void japi_setcursor(int obj, int value)
{
    send_3int(JAPI_CURSOR, obj, value);
}

void japi_setresizable(int obj, bool value)
{
    send_3int(JAPI_SETRESIZABLE, obj, value);
}

int japi_getlength(int obj)
{
    return send_2int_get_int(JAPI_GETLENGTH, obj);
}

int japi_getvalue(int obj)
{
    return send_2int_get_int(JAPI_GETVALUE, obj);
}

int japi_getdanger(int obj)
{
    return send_2int_get_int(JAPI_GETDANGER, obj);
}

int japi_getscreenheight()
{
    return send_2int_get_int(JAPI_GETSCREENHEIGHT, DUMMYOBJ);
}

int japi_getscreenwidth()
{
    return send_2int_get_int(JAPI_GETSCREENWIDTH, DUMMYOBJ);
}

int japi_getheight(int obj)
{
    return send_2int_get_int(JAPI_GETHEIGHT, obj);
}

int japi_getwidth(int obj)
{
    return send_2int_get_int(JAPI_GETWIDTH, obj);
}

int japi_getinsets(int obj, int pos)
{
    return send_3int_get_int(JAPI_GETINSETS, obj, pos);
}

int japi_getlayoutid(int obj)
{
    return send_2int_get_int(JAPI_GETLAYOUTID, obj);
}

int japi_getinheight(int obj)
{
    return send_2int_get_int(JAPI_GETINHEIGHT, obj);
}

int japi_getinwidth(int obj)
{
    return send_2int_get_int(JAPI_GETINWIDTH, obj);
}

string japi_gettext(int obj, retstr s)
{
    if (s == NULL)
	s = GC_malloc_atomic(japi_getlength(obj) + 1);
    send_2int_get_string(JAPI_GETTEXT, obj, s);
    return s;
}

string japi_getitem(int obj, int nr, retstr s)
{
    if (s == NULL)
	s = GC_malloc_atomic(MAXPATH);
    send_3int_get_string(JAPI_GETITEM, obj, nr, s);
    return s;
}

int japi_getitemcount(int obj)
{
    return send_2int_get_int(JAPI_GETITEMCOUNT, obj);
}

void japi_delete(int obj, int start, int end)
{
    send_4int(JAPI_DELETE, obj, start, end);
}

void japi_replacetext(int obj, string text, int start, int end)
{
    int len = strlen(text);

    send_5int(JAPI_REPLACETEXT, obj, start, end, len);
    send(commandstream, text, len, 0);
}

void japi_appendtext(int obj, string text)
{
    int len = strlen(text);

    send_3int(JAPI_APPENDTEXT, obj, len);
    send(commandstream, text, len, 0);
}

void japi_inserttext(int obj, string text, int pos)
{
    int len = strlen(text);

    send_4int(JAPI_INSERTTEXT, obj, pos, len);
    send(commandstream, text, len, 0);
}

void japi_settext(int obj, string text)
{
    int len = strlen(text);

    send_3int(JAPI_SETTEXT, obj, len);
    send(commandstream, text, len, 0);
}

void japi_selectall(int obj)
{
    send_2int(JAPI_SELECTALL, obj);
}

void japi_selecttext(int obj, int start, int end)
{
    send_4int(JAPI_SELECTTEXT, obj, start, end);
}

int japi_getselstart(int obj)
{
    return send_2int_get_int(JAPI_GETSELSTART, obj);
}

int japi_getselend(int obj)
{
    return (send_2int_get_int(JAPI_GETSELEND, obj));
}

string japi_getseltext(int obj, retstr s)
{
    if (s == NULL)
	s = GC_malloc_atomic(japi_getlength(obj));
    send_2int_get_string(JAPI_GETSELTEXT, obj, s);
    return s;
}

int japi_getcurpos(int obj)
{
    return send_2int_get_int(JAPI_GETCURPOS, obj);
}

void japi_setcurpos(int obj, int pos)
{
    send_3int(JAPI_SETCURPOS, obj, pos);
}

void japi_setechochar(int obj, char echo)
{
    send_2int_char(JAPI_SETECHOCHAR, obj, echo);
}

void japi_seteditable(int obj, bool val)
{
    send_3int(JAPI_EDITABLE, obj, val);
}

void japi_setshortcut(int obj, char c)
{
    send_2int_char(JAPI_SETSHORTCUT, obj, c);
}

void japi_quit()
{
    send_2int(JAPI_QUIT, DUMMYOBJ);
}

void japi_kill()
{
    send_2int(JAPI_KILL, DUMMYOBJ);
}

void japi_setsize(int obj, int width, int height)
{
    send_4int(JAPI_SETSIZE, obj, width, height);
}

int japi_getaction()
{
    if (get_message())
	return get_int(actionstream);
    else
	return 0;
}

int japi_nextaction()
{
    return get_int(actionstream);
}

void japi_show(int obj)
{
    send_2int(JAPI_SHOW, obj);
}

void japi_showpopup(int obj, int x, int y)
{
    send_4int(JAPI_SHOWPOPUP, obj, x, y);
}

void japi_add(int parent, int obj)
{
    send_3int(JAPI_ADD, parent, obj);
}

void japi_release(int obj)
{
    send_2int(JAPI_RELEASE, obj);
}

void japi_releaseall(int obj)
{
    send_2int(JAPI_RELEASEALL, obj);
}

void japi_hide(int obj)
{
    send_2int(JAPI_HIDE, obj);
}

void japi_dispose(int obj)
{
    send_2int(JAPI_DISPOSE, obj);
}

void japi_setpos(int obj, int x, int y)
{
    send_4int(JAPI_SETPOS, obj, x, y);
}

int japi_getviewportheight(int obj)
{
    return send_2int_get_int(JAPI_VIEWHEIGHT, obj);
}

int japi_getviewportwidth(int obj)
{
    return send_2int_get_int(JAPI_VIEWWIDTH, obj);
}

int japi_getxpos(int obj)
{
    return send_2int_get_int(JAPI_GETXPOS, obj);
}

int japi_getypos(int obj)
{
    return send_2int_get_int(JAPI_GETYPOS, obj);
}

void japi_getpos(int obj, varint x, varint y)
{
    *x = japi_getxpos(obj);
    *y = japi_getypos(obj);
}

int japi_getparentid(int obj)
{
    return send_2int_get_int(JAPI_GETPARENTID, obj);
}

void japi_setfocus(int obj)
{
    send_2int(JAPI_SETFOCUS, obj);
}

bool japi_hasfocus(int obj)
{
    return send_2int_get_int(JAPI_HASFOCUS, obj);
}

int japi_getstringwidth(int obj, string text)
{
    return send_2int_string_get_int(JAPI_STRINGWIDTH, obj, text);
}

int japi_getfontheight(int obj)
{
    return send_2int_get_int(JAPI_FONTHEIGHT, obj);
}

int japi_getfontascent(int obj)
{
    return send_2int_get_int(JAPI_FONTASCENT, obj);
}

/*			              L I S T E N E R S               */
int japi_keylistener(int component)
{
    return send_2int_get_int(JAPI_KEYLISTENER, component);
}

int japi_getkeycode(int keylst)
{
    return send_2int_get_int(JAPI_GETKEYCODE, keylst);
}

int japi_getkeychar(int keylst)
{
    return 255 & send_2int_get_int(JAPI_GETKEYCHAR, keylst);
}

int japi_mouselistener(int component, int kind)
{
    return send_3int_get_int(JAPI_MOUSELISTENER, component, kind);
}

int japi_getmousex(int mouselistener)
{
    return send_2int_get_int(JAPI_GETMOUSEX, mouselistener);
}

int japi_getmousey(int mouselistener)
{
    return send_2int_get_int(JAPI_GETMOUSEY, mouselistener);
}

void japi_getmousepos(int mouselistener, varint x, varint y)
{
    *x = japi_getmousex(mouselistener);
    *y = japi_getmousey(mouselistener);
}

int japi_getmousebutton(int mouselistener)
{
    return send_2int_get_int(JAPI_GETMOUSEBUTTON, mouselistener);
}

int japi_focuslistener(int component)
{
    return send_2int_get_int(JAPI_FOCUSLISTENER, component);
}

int japi_componentlistener(int component, int kind)
{
    return send_3int_get_int(JAPI_COMPONENTLISTENER, component, kind);
}

int japi_windowlistener(int window, int kind)
{
    return send_3int_get_int(JAPI_WINDOWLISTENER, window, kind);
}

/*             L A Y O U T M A N A G E R                    */

void japi_setflowlayout(int container, int orient)
{
    send_3int(JAPI_FLOWLAYOUT, container, orient);
}

void japi_setborderlayout(int container)
{
    send_2int(JAPI_BORDERLAYOUT, container);
}

void japi_setgridlayout(int container, int row, int col)
{
    send_4int(JAPI_GRIDLAYOUT, container, row, col);
}

void japi_setfixlayout(int container)
{
    send_2int(JAPI_FIXLAYOUT, container);
}

void japi_setnolayout(int container)
{
    send_2int(JAPI_NOLAYOUT, container);
}

void japi_setborderpos(int obj, int pos)
{
    send_3int(JAPI_BORDERPOS, obj, pos);
}

void japi_sethgap(int obj, int gap)
{
    send_3int(JAPI_SETHGAP, obj, gap);
}

void japi_setvgap(int obj, int gap)
{
    send_3int(JAPI_SETVGAP, obj, gap);
}

void japi_setinsets(int obj, int t, int b, int l, int r)
{
    send_6int(JAPI_SETINSETS, obj, t, b, l, r);
}

void japi_setalign(int obj, int align)
{
    send_3int(JAPI_SETALIGN, obj, align);
}

void japi_setflowfill(int obj, bool fill)
{
    send_3int(JAPI_FILLFLOWLAYOUT, obj, fill);
}

/*			G R A P H I C                          */

void japi_translate(int component, int x1, int y1)
{
    send_4int(JAPI_TRANSLATE, component, x1, y1);
}

void japi_cliprect(int component, int x1, int y1, int x2, int y2)
{
    if (x2 < 0)
	x1 += x2, x2 = -x2;
    if (y2 < 0)
	y1 += y2, y2 = -y2;
    send_6int(JAPI_CLIPRECT, component, x1, y1, x2, y2);
}

void japi_drawrect(int component, int x1, int y1, int x2, int y2)
{
    if (x2 < 0)
	x1 += x2, x2 = -x2;
    if (y2 < 0)
	y1 += y2, y2 = -y2;
    send_6int(JAPI_DRAWRECT, component, x1, y1, x2, y2);
}

void japi_fillrect(int component, int x1, int y1, int x2, int y2)
{
    if (x2 < 0)
	x1 += x2, x2 = -x2;
    if (y2 < 0)
	y1 += y2, y2 = -y2;
    send_6int(JAPI_FILLRECT, component, x1, y1, x2, y2);
}

void japi_drawroundrect(int component, int x1, int y1, int x2, int y2, int a,
                        int b)
{
    if (x2 < 0)
	x1 += x2, x2 = -x2;
    if (y2 < 0)
	y1 += y2, y2 = -y2;
    a *= 2;
    b *= 2;
    send_8int(JAPI_ROUNDRECT, component, x1, y1, x2, y2, a, b);
}

void japi_fillroundrect(int component, int x1, int y1, int x2, int y2, int a,
                        int b)
{
    if (x2 < 0)
	x1 += x2, x2 = -x2;
    if (y2 < 0)
	y1 += y2, y2 = -y2;
    a *= 2;
    b *= 2;
    send_8int(JAPI_FILLROUNDRECT, component, x1, y1, x2, y2, a, b);
}

void japi_drawoval(int component, int x, int y, int r1, int r2)
{
    if (r1 < 0)
	r1 = -r1;
    if (r2 < 0)
	r2 = -r2;
    x -= r1;
    y -= r2;
    r1 *= 2;
    r2 *= 2;
    send_6int(JAPI_DRAWOVAL, component, x, y, r1, r2);
}

void japi_filloval(int component, int x, int y, int r1, int r2)
{
    if (r1 < 0)
	r1 = -r1;
    if (r2 < 0)
	r2 = -r2;
    x -= r1;
    y -= r2;
    r1 *= 2;
    r2 *= 2;
    send_6int(JAPI_FILLOVAL, component, x, y, r1, r2);
}

void japi_drawcircle(int component, int x1, int y1, int r)
{
    if (r < 0)
	r = -r;
    x1 -= r;
    y1 -= r;
    r *= 2;
    send_6int(JAPI_DRAWOVAL, component, x1, y1, r, r);
}

void japi_fillcircle(int component, int x1, int y1, int r)
{
    int x2, y2;

    if (r < 0)
	r = -r;
    x1 -= r;
    y1 -= r;
    x2 = 2 * r;
    y2 = 2 * r;
    send_6int(JAPI_FILLOVAL, component, x1, y1, x2, y2);
}

void japi_drawarc(int component, int x, int y, int r1, int r2, int a, int b)
{
    if (r1 < 0)
	r1 = -r1;
    if (r2 < 0)
	r2 = -r2;
    x -= r1;
    y -= r2;
    r1 *= 2;
    r2 *= 2;
    b -= a;
    send_8int(JAPI_DRAWARC, component, x, y, r1, r2, a, b);
}

void japi_fillarc(int component, int x, int y, int r1, int r2, int a, int b)
{
    if (r1 < 0)
	r1 = -r1;
    if (r2 < 0)
	r2 = -r2;
    x -= r1;
    y -= r2;
    r1 *= 2;
    r2 *= 2;
    b -= a;
    send_8int(JAPI_FILLARC, component, x, y, r1, r2, a, b);
}

void japi_drawline(int component, int x1, int y1, int x2, int y2)
{
    send_6int(JAPI_DRAWLINE, component, x1, y1, x2, y2);
}

void japi_drawpolyline(int component, int n, intarr x, intarr y)
{
    send_3int(JAPI_POLYLINE, component, n);
    send_intarray(x, n);
    send_intarray(y, n);
}

void japi_drawpolygon(int component, int n, intarr x, intarr y)
{
    send_3int(JAPI_POLYGON, component, n);
    send_intarray(x, n);
    send_intarray(y, n);
}

void japi_fillpolygon(int component, int n, intarr x, intarr y)
{
    send_3int(JAPI_FILLPOLYGON, component, n);
    send_intarray(x, n);
    send_intarray(y, n);
}

void japi_drawpixel(int component, int x, int y)
{
    send_6int(JAPI_DRAWLINE, component, x, y, x, y);
}

void japi_drawstring(int component, int x, int y, string text)
{
    send_4int_string(JAPI_DRAWSTRING, component, x, y, text);
}

void japi_setxor(int component, bool b)
{
    send_3int(JAPI_SETXOR, component, b);
}

int japi_getimage(int component)
{
    return send_2int_get_int(JAPI_GETIMAGE, component);
}

void japi_getimagesource(int component, int sx, int sy, int sw, int sh,
                         varintarr r, varintarr g, varintarr b)
{
    char *buf;
    int i;

    buf = GC_malloc_atomic(sw * sh);
    send_6int(JAPI_GETIMAGESOURCE, component, sx, sy, sw, sh);
    socket_read(commandstream, buf, sw * sh);
    for (i = 0; i < sw * sh; i++)
	r[i] = buf[i];
    socket_read(commandstream, buf, sw * sh);
    for (i = 0; i < sw * sh; i++)
	g[i] = buf[i];
    socket_read(commandstream, buf, sw * sh);
    for (i = 0; i < sw * sh; i++)
	b[i] = buf[i];
}

void japi_drawimagesource(int component, int sx, int sy, int sw, int sh,
                          intarr r, intarr g, intarr b)
{
    char *buf;
    int i;

    buf = GC_malloc_atomic(sw * sh);
    send_6int(JAPI_DRAWIMAGESOURCE, component, sx, sy, sw, sh);
    for (i = 0; i < sw * sh; i++)
	buf[i] = (char)r[i];
    send(commandstream, buf, sw * sh, 0);
    for (i = 0; i < sw * sh; i++)
	buf[i] = (char)g[i];
    send(commandstream, buf, sw * sh, 0);
    for (i = 0; i < sw * sh; i++)
	buf[i] = (char)b[i];
    send(commandstream, buf, sw * sh, 0);
}

int japi_getscaledimage(int component, int sx, int sy, int sw, int sh, int dw,
                        int dh)
{
    send_6int(JAPI_GETSCALEDIMAGE, component, sx, sy, sx + sw, sy + sh);
    return send_2int_get_int(dw, dh);
}

void japi_drawimage(int component, int image, int x, int y)
{
    send_5int(JAPI_DRAWIMAGE, component, image, x, y);
}

void japi_drawscaledimage(int component, int image, int sx, int sy, int sw,
                          int sh, int dx, int dy, int dw, int dh)
{
    add_3int(JAPI_DRAWSCALEDIMAGE, component, image);
    add_4int(sx, sy, sx + sw, sy + sh);
    send_4int(dx, dy, dx + dw, dy + dh);
}

void japi_setcolor(int component, int red, int green, int blue)
{
    char c;

    add_2int(JAPI_FOREGROUNDCOLOR, component);
    c = (char)red;
    add_char(c);
    c = (char)green;
    add_char(c);
    c = (char)blue;
    send_char(c);
}

void japi_setcolorbg(int component, int red, int green, int blue)
{
    char c;

    add_2int(JAPI_BACKGROUNDCOLOR, component);
    c = (char)red;
    add_char(c);
    c = (char)green;
    add_char(c);
    c = (char)blue;
    send_char(c);
}

void japi_setnamedcolor(int component, int farbe)
{
    japi_setcolor(component, cga_color[farbe % MAXNAMEDCOLORS][0],
		  cga_color[farbe % MAXNAMEDCOLORS][1],
		  cga_color[farbe % MAXNAMEDCOLORS][2]);
}

void japi_setnamedcolorbg(int component, int farbe)
{
    japi_setcolorbg(component, cga_color[farbe % MAXNAMEDCOLORS][0],
		    cga_color[farbe % MAXNAMEDCOLORS][1],
		    cga_color[farbe % MAXNAMEDCOLORS][2]);
}

int japi_loadimage(string filename)
{
    int w, h, image;
    char *r, *g, *b;
    FILE *fd;
    char fname[MAXPATH];

    if ((fd = fopen(filename, "rb")) == NULL)
	return -1;
    if (__read_image(fd, &r, &g, &b, &w, &h) >= 0) {
	/* PPM and BMP */
	if ((image = japi_image(w, h)) < 0)
	    return -1;
	send_6int(JAPI_DRAWIMAGESOURCE, image, 0, 0, w, h);
	send(commandstream, r, w * h, 0);
	send(commandstream, g, w * h, 0);
	send(commandstream, b, w * h, 0);
	fclose(fd);
	return image;
    } else {
	/* GIF and JPEG */
	fclose(fd);
	sprintf(fname, "%s", filename);
	send_2int_string(JAPI_LOADIMAGE, DUMMYOBJ, tmpname(fname));
	httpsend();
	return get_int(commandstream);
    }
    return -1;
}

bool japi_saveimage(int drawable, string filename, int format)
{
    int w, h, image;
    char *r, *g, *b;
    FILE *fd;

    if ((fd = fopen(filename, "wb")) == NULL)
	return -1;
    w = japi_getwidth(drawable);
    h = japi_getheight(drawable);
    if (w * h <= 0)
	return -1;
    r = GC_malloc_atomic(w * h);
    g = GC_malloc_atomic(w * h);
    b = GC_malloc_atomic(w * h);

    /* Bug JAVA1.3 Linux, can't grab image direct */
    image = japi_image(w, h);
    japi_drawimage(image, drawable, 0, 0);
    send_6int(JAPI_GETIMAGESOURCE, image, 0, 0, w, h);

    socket_read(commandstream, r, w * h);
    socket_read(commandstream, g, w * h);
    socket_read(commandstream, b, w * h);
    if (__write_image(fd, r, g, b, w, h, format) < 0)
	return J_FALSE;
    fclose(fd);
    return J_TRUE;
}

/*			N U E T Z L I C H E S                     */
void japi_sync()
{
    send_2int_get_int(JAPI_SYNC, DUMMYOBJ);
}

void japi_beep()
{
    send_2int(JAPI_BEEP, DUMMYOBJ);
}

int japi_random()
{
#ifdef __GNUC__
    return random();
#else
    return (rand() << 16) + rand();
#endif
}

void japi_sleep(int msecs)
{
    msleep(msecs);
}

/* special scriba function  */
int __scriba_getimagesource(int component, int sx, int sy, int sw, int sh,
                            int **r, int **g, int **b)
{
    if (*r == NULL)
	*r = (int *)GC_malloc_atomic(sw * sh * sizeof(int));
    if (*g == NULL)
	*g = (int *)GC_malloc_atomic(sw * sh * sizeof(int));
    if (*b == NULL)
	*b = (int *)GC_malloc_atomic(sw * sh * sizeof(int));
    japi_getimagesource(component, sx, sy, sw, sh, (int *)*r, (int *)*g,
			(int *)*b);
    return sw * sh;
}
