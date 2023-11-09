#include <osg/Group>
#include <osgDB/ReadFile>
#include <osgViewer/Viewer>

int main()
{
	// 首先载入两个不同的模型，然后将其赋值给osg::Node指针。
	// 载入的模型同时也是一个通过组合节点与叶子节点构建的子场景图
	// osg::Node类能表示任意类型的子场景图
	osg::ref_ptr<osg::Node> model1 = osgDB::readNodeFile("cessna.osg");
	osg::ref_ptr<osg::Node> model2 = osgDB::readNodeFile("cow.osg");

	osg::ref_ptr<osg::Group> root = new osg::Group;
	osg::ref_ptr<osg::Group> root1 = new osg::Group;

	root->addChild(model1.get());
	root1->addChild(model2.get());

	osgViewer::Viewer viewer;
	viewer.setSceneData(root.get());
	viewer.setSceneData(root1.get());
	return viewer.run();
}