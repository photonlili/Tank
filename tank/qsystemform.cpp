#include "qsystemform.h"
#include "ui_qsystemform.h"


#include "qtankdefine.h"
#include "qtanklinux.h"

typedef struct tagCPU_OCCUPY          //定义一个cpu occupy的结构体
{
    char name[20];      //定义一个char类型的数组名name有20个元素
    unsigned int user; //定义一个无符号的int类型的user
    unsigned int nice; //定义一个无符号的int类型的nice
    unsigned int system;//定义一个无符号的int类型的system
    unsigned int idle; //定义一个无符号的int类型的idle
}CPU_OCCUPY;

typedef struct tagMEM_OCCUPY         //定义一个mem occupy的结构体
{
    char name[20];      //定义一个char类型的数组名name有20个元素
    unsigned long total;
    char name2[20];
    unsigned long free;
}MEM_OCCUPY;

void get_memoccupy (MEM_OCCUPY *mem) //对无类型get函数含有一个形参结构体类弄的指针O
{
    FILE *fd;
    int n;
    char buff[256];
    MEM_OCCUPY *m;
    m=mem;

    fd = fopen ("/proc/meminfo", "r");

    fgets (buff, sizeof(buff), fd);
    fgets (buff, sizeof(buff), fd);
    fgets (buff, sizeof(buff), fd);
    fgets (buff, sizeof(buff), fd);
    sscanf (buff, "%s %u %s", m->name, &m->total, m->name2);

    fgets (buff, sizeof(buff), fd); //从fd文件中读取长度为buff的字符串再存到起始地址为buff这个空间里
    sscanf (buff, "%s %u", m->name2, &m->free, m->name2);

    fclose(fd);     //关闭文件fd
}

int cal_cpuoccupy (CPU_OCCUPY *o, CPU_OCCUPY *n)
{
    unsigned long od, nd;
    unsigned long id, sd;
    int cpu_use = 0;

    od = (unsigned long) (o->user + o->nice + o->system +o->idle);//第一次(用户+优先级+系统+空闲)的时间再赋给od
    nd = (unsigned long) (n->user + n->nice + n->system +n->idle);//第二次(用户+优先级+系统+空闲)的时间再赋给od

    id = (unsigned long) (n->user - o->user);    //用户第一次和第二次的时间之差再赋给id
    sd = (unsigned long) (n->system - o->system);//系统第一次和第二次的时间之差再赋给sd
    if((nd-od) != 0)
        cpu_use = (int)((sd+id)*10000)/(nd-od); //((用户+系统)乖100)除(第一次和第二次的时间差)再赋给g_cpu_used
    else cpu_use = 0;
    //printf("cpu: %u/n",cpu_use);
    return cpu_use;
}

void get_cpuoccupy (CPU_OCCUPY *cpust) //对无类型get函数含有一个形参结构体类弄的指针O
{
    FILE *fd;
    int n;
    char buff[256];
    CPU_OCCUPY *cpu_occupy;
    cpu_occupy=cpust;

    fd = fopen ("/proc/stat", "r");
    fgets (buff, sizeof(buff), fd);

    sscanf (buff, "%s %u %u %u %u", cpu_occupy->name, &cpu_occupy->user, &cpu_occupy->nice,&cpu_occupy->system, &cpu_occupy->idle);

    fclose(fd);
}

QSystemForm::QSystemForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QSystemForm)
{
    ui->setupUi(this);

#ifdef __MIPS_LINUX__
    setWindowFlags(Qt::FramelessWindowHint|Qt::WindowStaysOnTopHint);
    //setAttribute(Qt::WA_TranslucentBackground, true);
#endif

    timer = new QTimer(this);
    timer->setSingleShot(false);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateLabel()));
    timer->start(100);
}

QSystemForm::~QSystemForm()
{
    delete ui;
}

void QSystemForm::updateLabel()
{
    CPU_OCCUPY cpu;
    get_cpuoccupy(&cpu);
    ui->label_cpu->setText(QString("cpu: %1%").arg((100*(cpu.user+cpu.nice+cpu.system)/(cpu.user+cpu.nice+cpu.system+cpu.idle))));
}
