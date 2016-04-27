#include "hnprinter.h"
#include "stdlib.h"

void HNPrinter::print(QString pdf)
{
    // 此处不会影响打印质量，不必再调试
    QString cmd;
    QString path="./Output.pbm";

    cmd = cmd.sprintf("gs -q -dBATCH -dSAFER -dQUIET -dNOPAUSE -sPAPERSIZE=a4 -r600*600 -sDEVICE=pbmraw -sOutputFile=%s %s", path.toLatin1().data(), pdf.toLatin1().data());
    system(cmd.toLatin1().data());

    cmd = cmd.sprintf("foo2zjs -z3 -p9 -r600*600 %s > /dev/usb/lp0", path.toLatin1().data());
    system(cmd.toLatin1().data());
}
