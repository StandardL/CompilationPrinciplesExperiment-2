#include "mainwindow.h"
#include "ui_mainwindow.h"

using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // SLOTS
    connect(ui->btn_toNFA, SIGNAL(clicked(bool)), this, SLOT(BtnNFAClicked()));
    connect(ui->btn_toDFA, SIGNAL(clicked(bool)), this, SLOT(BtnDFAClicked()));
    connect(ui->btn_toMinDFA, SIGNAL(clicked(bool)), this, SLOT(BtnMinDFAClicked()));
    connect(ui->btn_toCode, SIGNAL(clicked(bool)), this, SLOT(BtntoCodeClicked()));
    connect(ui->btn_openfile, SIGNAL(clicked(bool)), this, SLOT(BtnOpenFileClicked()));
    connect(ui->btn_clear, SIGNAL(clicked(bool)), this, SLOT(BtnClearClicked()));

    // set icon
    QStyle* style = QApplication::style();
    QIcon icon_tsh = style->standardIcon(QStyle::SP_TrashIcon);
    QIcon icon_up = style->standardIcon(QStyle::SP_ArrowUp);
    QIcon icon_down  = style->standardIcon(QStyle::SP_ArrowDown);
    ui->btn_clear->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);  // 清除
    ui->btn_last->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);  // 上一个
    ui->btn_next->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);  // 下一个
    ui->btn_clear->setIcon(icon_tsh);
    ui->btn_last->setIcon(icon_up);
    ui->btn_next->setIcon(icon_down);

    input_index = -1;  // 初始化为-1
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::BtnOpenFileClicked()
{
    word2vec.clear();
    auto filePath = QFileDialog::getOpenFileName(nullptr, tr("打开正则表达式"), QDir::currentPath());
    if (!filePath.isEmpty())
    {
        // 尝试打开文件
        QFile file(filePath);
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            // 创建一个 QTextStream 以按行读取文件
            QTextStream in(&file);

            // 逐行读取文件并保存在一个vector中
            while (!in.atEnd()) {
                QString line = in.readLine();
                word2vec.emplace_back(line);
            }

            // 关闭文件
            file.close();
        }
        else
        {
            QMessageBox::critical(this, "错误", "无法打开文件: " + filePath);
        }
    }
    max_index = word2vec.size();
    // 显示第一行的数据
    input_index = 0;
    ui->tb_input->setText(word2vec[0]);
}

void MainWindow::BtnClearClicked()
{
    ui->tb_input->clear();
    word2vec.clear();
    input_index = -1;
}

void MainWindow::BtnNFAClicked()
{
    if (ui->tb_input->text().isEmpty())  // 如果输入框文本为空，报错Return
    {
        QMessageBox::warning(NULL, tr("警告"), tr("输入框为空，不可进行该操作！"));
        return;
    }
    xlex.Reset();

    string input = ui->tb_input->text().toStdString();
    xlex.Read(input);
    xlex.toNFA();

    auto v = xlex.nfa_state_chart;  // copy一份表出来，在TableWidget中显示

    // 清空表格
    ui->tableMain->clear();

    // 设置行数和列数
    int rownum = xlex.nfa_end_node + 1;  // node从0开始，所以+1
    auto chars = xlex.GetChars();
    int charnum = chars.size();  // 字符数
    int colnum = charnum + 3;  // charnum表示当前输入有几个字符，然后加上第一列找开始和结束，第二列是点的编号，最后一列是#
    ui->tableMain->setRowCount(rownum);
    ui->tableMain->setColumnCount(colnum);
    // 禁止编辑
    ui->tableMain->setEditTriggers(QAbstractItemView::NoEditTriggers);
    // 设置标题（表头）
    auto qsl = QStringList() << " " << "结点编号";
    auto ncv = xlex.nfa_col_value;
    for (auto& i : ncv)  // 添加有的标题
    {
        qsl << QString(i.first);
    }
    qsl << "#";  // 终止符号
    ui->tableMain->setHorizontalHeaderLabels(qsl);

    // 添加开始和结束符的标记
    QTableWidgetItem* startItem = new QTableWidgetItem("-");
    ui->tableMain->setItem(xlex.nfa_start_node, 0, startItem);
    QTableWidgetItem* endItem = new QTableWidgetItem("+");
    ui->tableMain->setItem(xlex.nfa_end_node, 0, endItem);
    // 添加数据
    for (int row = 0; row < rownum; row++)
    {
        QString qrow = QString::number(row);
        // 设置下标
        QTableWidgetItem* idItem = new QTableWidgetItem(qrow);
        ui->tableMain->setItem(row, 1, idItem);

        // 添加数据
        for (int col = 0; col < charnum+1; col++)  // 字符数+1不要忘记"空#"
        {
            string out;
            for (auto& d : xlex.nfa_state_chart[row][col])
            {
                out += to_string(d) + ",";
            }
            if (out.empty()) continue;  // 如果是空就不需要加点
            out.erase(out.end() - 1);
            QTableWidgetItem* item = new QTableWidgetItem(QString::fromStdString(out));
            ui->tableMain->setItem(row, col+2, item);  // col+2是避免和前两列冲突
            item->setToolTip(QString::fromStdString(out));  // 鼠标悬浮完整显示
        }
    }

    // 自动调整列宽（可选）
    ui->tableMain->resizeColumnsToContents();
}

void MainWindow::BtnDFAClicked()
{
    if (ui->tb_input->text().isEmpty())  // 如果输入框文本为空，报错Return
    {
        QMessageBox::warning(NULL, tr("警告"), tr("输入框为空，不可进行该操作！"));
        return;
    }
    xlex.Reset();
    string input = ui->tb_input->text().toStdString();
    xlex.Read(input);
    xlex.toDFA();

    auto v = xlex.dfa_state_chart;  // copy一份表出来，在TableWidget中显示

    // 清空表格
    ui->tableMain->clear();

    // 设置行数和列数
    int rownum = xlex.DFA.NumofVertixes();
    auto chars = xlex.GetChars();
    int charnum = chars.size();  // 字符数
    int colnum = charnum + 2;  // charnum表示当前输入有几个字符，然后加上第一列找开始和结束，第二列是点的编号
    ui->tableMain->setRowCount(rownum);
    ui->tableMain->setColumnCount(colnum);
    // 禁止编辑
    ui->tableMain->setEditTriggers(QAbstractItemView::NoEditTriggers);
    // 设置标题（表头）
    auto qsl = QStringList() << " " << "状态集合";
    auto ncv = xlex.nfa_col_value;
    for (auto& i : ncv)  // 添加有的标题
    {
        qsl << QString(i.first);
    }
    ui->tableMain->setHorizontalHeaderLabels(qsl);

    // 添加数据
    for (int row = 0; row < rownum; row++)
    {
        // 设置下标，此处是显示状态集合
        string s;
        s += "{";
        for (auto& e : xlex.dfa_state_chart[row][0])
        {
            s += to_string(e);
            s += ",";
        }
        s.erase(s.end() - 1);
        s += "}";
        QTableWidgetItem* idItem = new QTableWidgetItem(QString::fromStdString(s));
        ui->tableMain->setItem(row, 1, idItem);
        idItem->setToolTip(QString::fromStdString(s));
        // 查查有无开始元素或者结束元素
        if (s.find(to_string(xlex.nfa_start_node)) < s.length())
        {
            QTableWidgetItem* startItem = new QTableWidgetItem("-");
            ui->tableMain->setItem(row, 0, startItem);
        }
        else if (s.find(to_string(xlex.nfa_end_node)) < s.length())
        {
            QTableWidgetItem* endItem = new QTableWidgetItem("+");
            ui->tableMain->setItem(row, 0, endItem);
        }
        // 添加数据
        for (int col = 1; col <= charnum; col++)
        {
            string out = "{";
            for (auto& d : xlex.dfa_state_chart[row][col])
            {
                out += to_string(d) + ",";
            }
            if (out.length() == 1) continue;  // 如果是空就不需要加点
            out.erase(out.end() - 1);
            out.append("}");
            QTableWidgetItem* item = new QTableWidgetItem(QString::fromStdString(out));
            ui->tableMain->setItem(row, col+1, item);  // col+1是避免和前两列冲突
            item->setToolTip(QString::fromStdString(out));  // 鼠标悬浮完整显示
        }
    }

    // 自动调整列宽（可选）
    ui->tableMain->resizeColumnsToContents();
}

void MainWindow::BtnMinDFAClicked()
{
    if (ui->tb_input->text().isEmpty())  // 如果输入框文本为空，报错Return
    {
        QMessageBox::warning(NULL, tr("警告"), tr("输入框为空，不可进行该操作！"));
        return;
    }
    xlex.Reset();
    string input = ui->tb_input->text().toStdString();
    xlex.Read(input);
    xlex.toMinDFA();

    auto v = xlex.min_state_chart;  // copy一份表出来，在TableWidget中显示

    // 清空表格
    ui->tableMain->clear();

    // 设置行数和列数
    int rownum = xlex.minDFA_t.NumofVertixes();
    auto chars = xlex.GetChars();
    int charnum = chars.size();  // 字符数
    int colnum = charnum + 2;  // charnum表示当前输入有几个字符，然后加上第一列找开始和结束，第二列是点的编号
    ui->tableMain->setRowCount(rownum);
    ui->tableMain->setColumnCount(colnum);
    // 禁止编辑
    ui->tableMain->setEditTriggers(QAbstractItemView::NoEditTriggers);
    // 设置标题（表头）
    auto qsl = QStringList() << " " << "MinDFA结点编号";
    auto ncv = xlex.nfa_col_value;
    for (auto& i : ncv)  // 添加有的标题
    {
        qsl << QString(i.first);
    }
    ui->tableMain->setHorizontalHeaderLabels(qsl);

    // 添加数据
    for (int row = 0; row < rownum; row++)
    {
        // 设置下标，此处是显示状态集合
        string s;
        s += "{";
        for (auto& e : xlex.min_state_chart[row][0])
        {
            s += to_string(e);
            s += ",";
        }
        s.erase(s.end() - 1);
        s += "}";
        QTableWidgetItem* idItem = new QTableWidgetItem(QString::fromStdString(s));
        ui->tableMain->setItem(row, 1, idItem);
        idItem->setToolTip(QString::fromStdString(s));
        // 开始元素
        QTableWidgetItem* startItem = new QTableWidgetItem("-");
        ui->tableMain->setItem(row, 0, startItem);
        // 结束元素
        if (xlex.isAccepted[row])
        {
            string end = "+";
            if (row == 0)
                end = "-/+";
            QTableWidgetItem* endItem = new QTableWidgetItem(QString::fromStdString(end));
            ui->tableMain->setItem(row, 0, endItem);
        }
        // 添加数据
        for (int col = 1; col <= charnum; col++)
        {
            string out = "{";
            for (auto& d : xlex.min_state_chart[row][col])
            {
                out += to_string(d) + ",";
            }
            if (out.length() == 1) continue;  // 如果是空就不需要加点
            out.erase(out.end() - 1);
            out.append("}");
            QTableWidgetItem* item = new QTableWidgetItem(QString::fromStdString(out));
            ui->tableMain->setItem(row, col+1, item);  // col+1是避免和前两列冲突
            item->setToolTip(QString::fromStdString(out));  // 鼠标悬浮完整显示
        }
    }

    // 自动调整列宽（可选）
    ui->tableMain->resizeColumnsToContents();
}

void MainWindow::BtntoCodeClicked()
{
    if (ui->tb_input->text().isEmpty())  // 如果输入框文本为空，报错Return
    {
        QMessageBox::warning(NULL, tr("警告"), tr("输入框为空，不可进行该操作！"));
        return;
    }
    xlex.Reset();
    string input = ui->tb_input->text().toStdString();
    xlex.Read(input);
    auto filePath = QFileDialog::getSaveFileName(nullptr, tr("保存为C++代码"), QDir::currentPath(), tr("C++ 文件 (*.cpp)"));
    if (filePath.isEmpty())
    {
        QMessageBox::critical(this, "取消", "用户取消选择了文件名");
        return;
    }
    string stdFilePath = string(filePath.toLocal8Bit());
    xlex.ShowCode(stdFilePath);

    QMessageBox::information(this, "成功", "导出成功！关闭此窗口后即可打开！");
    ShellExecuteA(NULL, "open", stdFilePath.c_str(), NULL, NULL, SW_SHOW);
}

void MainWindow::on_btn_last_clicked()
{
    input_index++;
    input_index %= max_index;
    ui->tb_input->setText(word2vec[input_index]);
}


void MainWindow::on_btn_next_clicked()
{
    input_index--;
    if (input_index < 0)
        input_index += max_index;
    ui->tb_input->setText(word2vec[input_index]);
}

