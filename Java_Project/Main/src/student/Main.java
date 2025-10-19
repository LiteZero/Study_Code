package student;

import java.io.ObjectStreamException;
import java.util.Objects;
import java.util.Scanner;

import static java.lang.System.exit;


public class Main {
    static String[] arg = new String[0];
    static student[] students;//创建一个student类数组用于存储相关数据
    public static void showStudents(int i) {
        System.out.println("====================");
        System.out.println("学号:"+students[i].num);
        System.out.println("姓名:"+students[i].name);
        System.out.println("性别:"+students[i].sex);
        System.out.println("班级:"+students[i].class_num);
        System.out.println("语文成绩:"+students[i].score_chinese);
        System.out.println("数学成绩:"+students[i].score_math);
        System.out.println("====================");
    }
    public static int functionSelect(){
        Scanner sc = new Scanner(System.in);
        System.out.println(" ");
        System.out.println("欢迎使用小学信息管理软件！");
        System.out.println("====================");
        System.out.println("1.初始化学生信息");
        System.out.println("2.显示学生信息");
        System.out.println("3.查询指定学生信息");
        System.out.println("4.查询班级平均分");
        System.out.println("5.求不及格的学生");
        System.out.println("6.修改学生成绩");
        System.out.println("7.退出该软件");
        System.out.println("====================");
        System.out.print("请输入要使用的功能：");
        return sc.nextInt();
    }
    //初始化学生信息：
    public static void getReadyForStudentMessage() throws InterruptedException {
        Scanner sc = new Scanner(System.in);
        System.out.print("请输入学生的人数：");
        students = new student[sc.nextInt()];
        for(int i=0;i<students.length;i++){
            sc.nextLine();//防止前面输入人数处多输入一个回车被读取
            students[i] = new student();
            System.out.print("请输入第"+(i+1)+"名学生的学号：");
            students[i].num=sc.nextLine();
            System.out.print("请输入第"+(i+1)+"名学生的姓名：");
            students[i].name=sc.nextLine();
            System.out.print("请输入第"+(i+1)+"名学生的性别：");
            students[i].sex=sc.nextLine();
            System.out.print("请输入第"+(i+1)+"名学生的班级：");
            students[i].class_num=sc.nextLine();
            System.out.print("请输入第"+(i+1)+"名学生的语文分数：");
            students[i].score_chinese=sc.nextFloat();
            System.out.print("请输入第"+(i+1)+"名学生的数学分数：");
            students[i].score_math=sc.nextFloat();
        }
        System.out.println("已输入完毕，返回到上一页...");//执行完该操作后 返回到选择操作处的代码
        main(arg);
    }
    //显示学生信息：
    public static void showStudentMessage() throws InterruptedException {
        for(int i=0;i<students.length;i++){
            showStudents(i);
        }
        System.out.println("已输出完毕，返回到上一页...");//执行完该操作后 返回到选择操作处的代码
        main(arg);
    }
    //查询指定学生信息：
    public static void checkForStudentMessage() throws InterruptedException {
        System.out.print("请输入要查询的学生信息学号：");
        Scanner sc = new Scanner(System.in);
        String checkNum=sc.nextLine();
        for(int i=0;i<students.length;i++){
            if(Objects.equals(checkNum, students[i].num)){//比较字符串值
                showStudents(i);
                break;
            }
            if(i==students.length-1){System.out.println("未找到该学号的学生");break;}
        }
        System.out.println("已输出完毕，返回到上一页...");//执行完该操作后 返回到选择操作处的代码
        main(arg);
    }
    //查询班级平均分：
    public static void checkClassScoreAve() throws InterruptedException {
        Scanner sc = new Scanner(System.in);
        System.out.print("请输入要查询的班级：");
        String checkClass=sc.nextLine();
        System.out.print("请输入要查询的科目（语文或数学）：");
        String checkkemu=sc.nextLine();
        if(!Objects.equals(checkkemu, "语文")&&!Objects.equals(checkkemu,"数学")){System.out.println("输入的科目非法,退出该功能中...");main(arg);exit(0);}
        double scoreAve=0;
        int peoplenum=0;
        for(int i=0;i<students.length;i++){
            if(Objects.equals(checkClass, students[i].class_num)){
                peoplenum++;
                if(Objects.equals(checkkemu, "语文")){scoreAve+=students[i].score_chinese;}
                else {scoreAve+=students[i].score_math;}
            }
            scoreAve=scoreAve/(peoplenum);
        }
        System.out.println("该班所求科目的平均分为："+scoreAve);
        System.out.println("已输出完毕，返回到上一页...");//执行完该操作后 返回到选择操作处的代码
        main(arg);
    }
    //求不合格的学生名单:
    public static void checkUn60StudentMessge() throws InterruptedException {
        System.out.print("请输入要查询的科目（语文或数学）：");
        Scanner sc = new Scanner(System.in);
        String checkkemu=sc.nextLine();
        if(!Objects.equals(checkkemu, "语文")&&!Objects.equals(checkkemu,"数学")){System.out.println("输入的科目非法,退出该功能中...");main(arg);exit(0);}
        for(int i=0;i<students.length;i++){
            if(Objects.equals(checkkemu, "语文")){
                if(students[i].score_chinese<60){
                    showStudents(i);
                }}
            else{if(students[i].score_math<60){
                showStudents(i);
            }}
        }
        System.out.println("已输出完毕，返回到上一页...");//执行完该操作后 返回到选择操作处的代码
        main(arg);
    }
    //修改学生成绩：
    public static void changeStudentScore() throws InterruptedException {
        Scanner sc = new Scanner(System.in);
        System.out.print("请输入要修改成绩的学生学号：");
        String changeScoreNum=sc.nextLine();
        System.out.print("请输入要修改成绩的科目（语文或数学）：");
        String changeKemu=sc.nextLine();
        if(!Objects.equals(changeKemu, "语文")&&!Objects.equals(changeKemu,"数学")){System.out.println("输入的科目非法,退出该功能中...");main(arg);exit(0);}
        System.out.print("将该成绩修改为：");
        float changeScore=sc.nextFloat();
        for(int i=0;i<students.length;i++){
            if(Objects.equals(changeScoreNum, students[i].num)){
                if (Objects.equals(changeKemu, "语文")){students[i].score_chinese=changeScore;}
                else {students[i].score_math=changeScore;}
                break;
            }
        }
        System.out.println("已输出完毕，返回到上一页...");//执行完该操作后 返回到选择操作处的代码
        main(arg);
    }
    public static void main(String[] args) throws InterruptedException {
        int use_func = functionSelect();
        switch (use_func){
            case 1:getReadyForStudentMessage();break;
            case 2:showStudentMessage();break;
            case 3:checkForStudentMessage();break;
            case 4:checkClassScoreAve();break;
            case 5:checkUn60StudentMessge();break;
            case 6:changeStudentScore();break;
            case 7:System.out.println("感谢您的使用，再见。");break;
            default:System.out.println("输入了错误的值，请重新输入");main(args);break;
        }
    }
}