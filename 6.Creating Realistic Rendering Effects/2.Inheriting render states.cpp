#include <osg/PolygonMode>
#include <osg/MatrixTransform>
#include <osgDB/ReadFile>
#include <osgViewer/Viewer>

int main()
{
	osg::ref_ptr<osg::Node> model = osgDB::readNodeFile(
		"cessna.osg");
	osg::ref_ptr<osg::MatrixTransform> transformation1 = new
		osg::MatrixTransform;
	transformation1->setMatrix(osg::Matrix::translate(
		-0.5f, 0.0f, 0.0f));
	transformation1->addChild(model.get());
	osg::ref_ptr<osg::MatrixTransform> transformation2 = new
		osg::MatrixTransform;
	transformation2->setMatrix(osg::Matrix::translate(
		0.5f, 0.0f, 0.0f));
	transformation2->addChild(model.get());

	osg::ref_ptr<osg::Group> root = new osg::Group;
	root->addChild(transformation1.get());
	root->addChild(transformation2.get());

	transformation1->getOrCreateStateSet()->setMode(GL_LIGHTING,
		osg::StateAttribute::OFF);
	transformation2->getOrCreateStateSet()->setMode(GL_LIGHTING,
		osg::StateAttribute::OFF | osg::StateAttribute::PROTECTED);
	root->getOrCreateStateSet()->setMode(GL_LIGHTING,
		osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);

	osgViewer::Viewer viewer;
	viewer.setSceneData(root.get());
	return viewer.run();
}

// 备注
// osg::StateAttribute::PROTECTED代表当前节点的状态属性被保护
// 不会被父节点或者祖先节点的状态覆盖
// transformation1光照效果关闭，后面被root覆盖了光照状态
// transformation2光照效果关闭但被保护了，所以root覆盖不了，所以显示的是transformation2自己的光照状态
// 由于该2节点关闭了其表面的“灯光”，所以他看起来有一些亮。这是因为几何现在是依据原始颜色数组来直接着色的，而没有对灯光的响应。