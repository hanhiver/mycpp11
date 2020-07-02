#include <iostream>
#include <boost/filesystem.hpp>

using namespace std;
using namespace boost::filesystem;

int main(int argc, char *argv[])
{
    string filePath = "/work/test/testPath";
    //string fileName = ".test_path.tar.gz";
    string fileName = ".test";

    //path("/work/test/testPath/test_path.txt");
    boost::filesystem::path testFilePath(filePath);

    // 使用'/'追加路径，并把路径转化成字符串
    string fullFilePath = (testFilePath/fileName).string();
    cout << "fullFilePath:" << fullFilePath << endl;

    if(!testFilePath.empty())
        cout << "path is not empty" << endl;
    // 取fullFilePath中的部分路径
    boost::filesystem::path workPath(fullFilePath.begin(),fullFilePath.begin()+5);
    cout << "workPath:" << workPath << endl;
    // 追加路径'/='
    workPath /= "testPath";
    cout << "workPath append path:" << workPath << endl;
    // 追加字符序列append
    workPath.append(fileName.begin(),fileName.end());
    cout << "workPath append string file:" << workPath << endl;

    // 返回当前文件系统下的绝对路径system_complete
    cout << "system_complete:" << system_complete(workPath) << endl;

    // 返回标准格式的文件路径string()
    cout << "string():" << workPath.string() << endl;

    // 返回文件通用路径
    if(workPath.is_absolute())
    cout << "generic_string():" << workPath.generic_string() << endl;

    // 返回路径中的父路径
    if(workPath.has_parent_path())
        cout << "parent_path():" << workPath.parent_path() << endl;

    // 不含扩展名的全路径
    if(workPath.has_stem())
        cout << "stem():" << workPath.stem() << endl;

    // 返回文件名
    if(workPath.has_filename())
        cout << "filename():" << workPath.filename() << endl;

    // 返回文件扩展名
    cout << "extension():" << workPath.extension() << endl;

    // 返回路径根目录
    if(workPath.has_root_path())
        cout << "root_path():" << workPath.root_path() << endl;

    // 返回根名称
    if(workPath.has_root_name())
        cout << "root_name():" << workPath.root_name() << endl;

    // 返回相对路径
    if(workPath.has_relative_path())
        cout << "relative_path():" << workPath.relative_path() << endl;

    // 返回root文件夹目录
    if(workPath.has_root_directory())
        cout << "root_directory():" << workPath.root_directory() << endl;

    // 变更文件扩展名(只是看起来像更改了，实际的文件名字并没有发生变化)
    cout << "replace_extension() remove:" << workPath.replace_extension() << endl; // 删除扩展名
    cout << "replace_extension() change:" << workPath.replace_extension("go") << endl; // 更改扩展名

    // 删除文件名
    cout << "remove_filename():" << workPath.remove_filename() << endl;

    cout << "Hello World!" << endl;
    return 0;
}
