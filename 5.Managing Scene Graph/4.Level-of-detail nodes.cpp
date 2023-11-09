#include <osg/LOD>
#include <osgDB/ReadFile>
#include <osgUtil/Simplifier>
#include <osgViewer/Viewer>

int main()
{
	// 级别3是原始，2,1是越来越远的显示效果
	osg::ref_ptr<osg::Node> modelL3 = osgDB::readNodeFile("cessna.osg");
	osg::ref_ptr<osg::Node> modelL2 = dynamic_cast<osg::Node*>(
			modelL3->clone(osg::CopyOp::DEEP_COPY_ALL));
	osg::ref_ptr<osg::Node> modelL1 = dynamic_cast<osg::Node*>(
		modelL3->clone(osg::CopyOp::DEEP_COPY_ALL));

	// osgUtil::Simplifier类在这里用来减少顶点数与面数
	// 使用不同的setSampleRation()方法，导致不同的缩放比率
	osgUtil::Simplifier simplifier;
	simplifier.setSampleRatio(0.5);
	modelL2->accept(simplifier);
	simplifier.setSampleRatio(0.1);
	modelL1->accept(simplifier);

	osg::ref_ptr<osg::LOD> root = new osg::LOD;
	root->addChild(modelL1.get(), 200.0f, FLT_MAX);
	root->addChild(modelL2.get(), 50.0f, 200.0f);
	root->addChild(modelL3.get(), 0.0f, 50.0f);

	osgViewer::Viewer viewer;
	viewer.setSceneData(root.get());
	return viewer.run();
}