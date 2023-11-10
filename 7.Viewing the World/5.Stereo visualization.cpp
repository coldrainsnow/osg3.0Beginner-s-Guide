#include <osgDB/ReadFile>
#include <osgViewer/Viewer>

int main()
{
	osg::DisplaySettings::instance()->setStereoMode(osg::DisplaySettings::ANAGLYPHIC);
	osg::DisplaySettings::instance()->setEyeSeparation(0.05f);
	osg::DisplaySettings::instance()->setStereo(true);

	osg::ref_ptr<osg::Node> model = osgDB::readNodeFile("cessna.osg");
	osgViewer::Viewer viewer;
	viewer.setSceneData(model.get());
	return viewer.run();
}