#include <osg/ProxyNode>
#include <osgViewer/Viewer>

int main()
{
	osg::ref_ptr<osg::ProxyNode> root = new osg::ProxyNode;
	root->setFileName(0, "cow.osg");

	osgViewer::Viewer viewer;
	viewer.setSceneData(root.get());
	return viewer.run();
}