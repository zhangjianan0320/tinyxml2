/*************************************************************************
    > File Name: main.cpp
    > Author: zjn
    > Mail:zjn 
    > Created Time: 2020年09月07日 星期一 10时14分13秒
 ************************************************************************/

#include<iostream>
#include "tinyxml2.h"
using namespace std;
//using namespace tinyxml2;

void example()
{
	tinyxml2::XMLDocument doc;
	doc.LoadFile("test.xml");	//从文件加载xml信息
	const char* content = doc.FirstChildElement("Hello")->GetText();
	printf("hello,%s\n",content);
	doc.Print();	//打印xml信息
}

void example1()
{	
	static const char * xml = 
	"<?xml version=\"1.0\"?>"
	"<!DOCTYPE PLAY SYSTEM \"play.dtd\">"
	"<PLAY>"
	"<TITLE>A Midsummer Night's Dream</TITLE>"
	"</PLAY>";

	tinyxml2::XMLDocument doc;
	doc.Parse(xml);	//从流中加载xml信息
	doc.Print();
	doc.SaveFile("example1.xml");

}

void example2()
{
	tinyxml2::XMLDocument doc;
	tinyxml2::XMLElement *element1=doc.NewElement("Element1");
	tinyxml2::XMLElement *element2=doc.NewElement("Element2");
	doc.InsertEndChild(element1);
	doc.InsertEndChild(element2);
	doc.InsertAfterChild(element2,element2);
	doc.InsertAfterChild(element2,element2);

	doc.Print();
	doc.SaveFile("example2.xml");
}

int test_tinyxml2_create()
{
	const char* declaration = "<?xml version=\"1.0\" encoding=\"utf-8\"?>";
	tinyxml2::XMLDocument doc;
	tinyxml2::XMLError ret = doc.Parse(declaration);
	if(ret!=0)
	{
		fprintf(stderr,"fail to parse xml file: %s\n",declaration);
		return -1;
	}
	tinyxml2::XMLComment* comment = doc.NewComment("this is a xml test file");
	doc.InsertEndChild(comment);

	tinyxml2::XMLElement* root = doc.NewElement("Root");
	doc.InsertEndChild(root);

	tinyxml2::XMLElement* user = doc.NewElement("User");
	user->SetAttribute("Name", "fengbingchun");
	root->InsertEndChild(user);

	tinyxml2::XMLElement* blog = doc.NewElement("Blog");
	tinyxml2::XMLText* text1 = doc.NewText("CSDN");
	blog->InsertEndChild(text1);
	user->InsertEndChild(blog);

	tinyxml2::XMLElement* code = doc.NewElement("Code");
	tinyxml2::XMLText* text2 = doc.NewText("GitHub");
	code->InsertEndChild(text2);
	user->InsertEndChild(code);

	tinyxml2::XMLElement* blog2 = doc.NewElement("Blog");
	blog2->SetAttribute("Name", "CSDN");
	root->InsertEndChild(blog2);

	tinyxml2::XMLElement* addr = doc.NewElement("Address");
	tinyxml2::XMLText* text3 = doc.NewText("https://blog.csdn.net/fengbingchun");
	addr->InsertEndChild(text3);
	blog2->InsertEndChild(addr);

	tinyxml2::XMLElement* id = doc.NewElement("ID");
	tinyxml2::XMLText* text4 = doc.NewText("fengbingchun");
	id->InsertEndChild(text4);
	blog2->InsertEndChild(id);

	tinyxml2::XMLElement* code2 = doc.NewElement("Code");
	code2->SetAttribute("Name", "GitHub");
	root->InsertEndChild(code2);
		 
	tinyxml2::XMLElement* addr2 = doc.NewElement("Address");
	tinyxml2::XMLText* text5 = doc.NewText("https://github.com//fengbingchun");
	addr2->InsertEndChild(text5);
	code2->InsertEndChild(addr2);
							
	tinyxml2::XMLElement* repositories = doc.NewElement("Repositories");
	tinyxml2::XMLText* text6 = doc.NewText("27");
	repositories->InsertEndChild(text6);
	code2->InsertEndChild(repositories);

	doc.SaveFile("test_tinyxml2_create.xml");
}

int test_tinyxml2_parse()
{
	const char* file_name = "test_tinyxml2_create.xml";
	tinyxml2::XMLDocument doc;
	tinyxml2::XMLError ret = doc.LoadFile(file_name);
	if (ret != 0) {
		fprintf(stderr, "fail to load xml file: %s\n", file_name);
		return -1;
	}
	tinyxml2::XMLElement* root = doc.RootElement();
	fprintf(stdout, "root element name: %s\n", root->Name());
		 
	// User
	tinyxml2::XMLElement* user = root->FirstChildElement("User");
	if (!user) {
		fprintf(stderr, "no child element: User\n");
		return -1;
	}
	fprintf(stdout, "user name: %s\n", user->Attribute("Name"));

	tinyxml2::XMLElement* blog = user->FirstChildElement("Blog");
	if (!blog) {
		fprintf(stderr, "no child element: Blog, in User\n");
	return -1;
	}
	fprintf(stdout, "blog value: %s\n", blog->GetText());
	fprintf(stdout, "code value: %s\n\n", user->FirstChildElement("Code")->GetText());

	tinyxml2::XMLElement* blog2 = root->FirstChildElement("Blog");
	if (!blog2) {
		fprintf(stderr, "no child element: Blog\n");
		return -1;
	}
	fprintf(stdout, "blog name: %s\n", blog2->Attribute("Name"));
	
	tinyxml2::XMLElement* addr = blog2->FirstChildElement("Address");
	if (!addr) {
		fprintf(stderr, "no child element: Address, in Blog\n");
		return -1;
	}
	fprintf(stdout, "address value: %s\n", addr->GetText());
	fprintf(stdout, "id value: %s\n\n", blog2->FirstChildElement("ID")->GetText());

	tinyxml2::XMLElement* code = root->FirstChildElement("Code");
	if (!code) {
		fprintf(stderr, "no child element: Code\n");
		return -1;
	}
	fprintf(stdout, "code name: %s\n", code->Attribute("Name"));
	 
	tinyxml2::XMLElement* addr2 = code->FirstChildElement("Address");
	if (!addr2) {
		fprintf(stderr, "no child element: Address, in Code\n");
		return -1;
	}
	fprintf(stdout, "address value: %s\n", addr2->GetText());
	fprintf(stdout, "repositories value: %s\n\n", code->FirstChildElement("Repositories")->GetText());
	return 0;

}

void create_xml(const char *file_name,const char *dec_info)
{
	tinyxml2::XMLDocument doc;
	if(doc.LoadFile(file_name) != 0)
	{
		printf("%s is not exised\n",file_name);
		//添加声明
		tinyxml2::XMLDeclaration *declaration = doc.NewDeclaration(dec_info); //创建描述信息
		doc.InsertFirstChild(declaration);	//将描述信息添加到信息中

		tinyxml2::XMLElement* root = doc.NewElement("SCHOOL");	//创建根节点
		doc.InsertEndChild(root);	//将根节点添加到文件中
//		doc.Print();
		doc.SaveFile(file_name);	
	}
}

typedef struct 
{
	int id;
	int age;
	int gender;
}Student;

//void creat_student(,)

void add_student(const char* filename,Student *stu)
{
	tinyxml2::XMLDocument doc;
	if(doc.LoadFile(filename) != 0)
	{
		printf("load failed!");
	}
	tinyxml2::XMLElement *root = doc.RootElement();	//	获取根节点
	tinyxml2::XMLElement* userNode = root->FirstChildElement("Base");

	tinyxml2::XMLElement *stu_info=doc.NewElement("Base");	//创建基本信息节点
	stu_info->SetAttribute("ID",stu->id);	//设置属性 可以设置多个

	tinyxml2::XMLElement *age = doc.NewElement("age");	//创建age节点
/*
	age->SetAttribute("age",stu->id);
*/

	char str[20];
	sprintf(str,"%d",stu->age);
	age->InsertFirstChild(doc.NewText(str));

	stu_info->InsertEndChild(age);

	root->InsertEndChild(stu_info);	//将基本信息节点添加到根中

	doc.Print();
	doc.SaveFile(filename);
}

void delet_student(const char* filename,int id)
{
	tinyxml2::XMLDocument doc;
	if(doc.LoadFile(filename) != 0)
	{
		printf("load failed!");
	}
	doc.Print();
	printf("xxxxxxx");
	tinyxml2::XMLElement *root = doc.RootElement();	//	获取根节点
	tinyxml2::XMLElement* userNode = root->FirstChildElement("Base");
	while(userNode != NULL)
	{
		if(atoi(userNode->Attribute("ID")) == id)
		{
			printf("delete\n");
			root->DeleteChild(userNode);
		}
		userNode = userNode->NextSiblingElement();
	}
	doc.Print();
	doc.SaveFile(filename);
}

void change_student(const char *filename,Student *stu)
{
	tinyxml2::XMLDocument doc;
	if(doc.LoadFile(filename) != 0)
	{
		printf("load failed!\n");
		return ;
	}
//	doc.Print();
	tinyxml2::XMLElement *root = doc.RootElement();
	tinyxml2::XMLElement *userNode = root->FirstChildElement("Base");

	while(userNode != NULL)
	{
		if(atoi(userNode->Attribute("ID")) == stu->id)
		{
			char str[20];
			sprintf(str,"%d",stu->age);
			userNode->FirstChildElement("age")->SetText(str);
		}
		userNode = userNode->NextSiblingElement();
	}
//	doc.Print();
	doc.SaveFile(filename);
	return ;
}
int main(int argc,char ** argv)
{
//	std::cout<<"tinyxml"<<endl;
#if 0
	example();
	printf("\n");
	example1();
	printf("\n");
	example2();
	test_tinyxml2_create();
	test_tinyxml2_parse();
#endif
	const char* filename = "student.xml";
	if(argc < 2)
	{
		std::cout<<"exmple "<< argv[0]<<" -a 0 10"<<"		//添加成员 id 0 age 10"<<endl;
		std::cout<<"exmple "<< argv[0]<<" -d 0"<<"		//删除成员 0"<<endl;
		std::cout<<"exmple "<< argv[0]<<" -c 0 11"<<"		//修改成员信息 id 0 age 11"<<endl;
		std::cout<<"exmple "<< argv[0]<<" -r 0"<<"		//读成员参数 id 0"<<endl;
		exit(-1);
	}
	create_xml(filename,"student info");
	Student stu1 = {3,88,0};

	
	
	if(strcmp(argv[1],"-a"))
	{
		printf("添加成员\n");
	}
	else if(strcmp(argv[1],"-d"))
	{
		printf("删除成员\n");
	}
	else if(strcmp(argv[1],"-c"))
	{
		printf("修改成员\n");
	}
	else if(strcmp(argv[1],"-r"))
	{
		printf("读取成员\n");
	}
	else
	{
		printf("input error\n");
	}
//	delet_student(filename,0);
//	add_student(filename,&stu1);
//	change_student(filename,&stu1);
	return 0;
}

