#include <osg/BlendFunc>
#include <osg/Texture2D>
#include <osg/Geometry>
#include <osgDB/ReadFile>
#include <osgViewer/Viewer>

int main()
{
	osg::ref_ptr<osg::Vec3Array> vertices = new osg::Vec3Array;
	vertices->push_back(osg::Vec3(-0.5f, 0.0f, -0.5f));
	vertices->push_back(osg::Vec3(0.5f, 0.0f, -0.5f));
	vertices->push_back(osg::Vec3(0.5f, 0.0f, 0.5f));
	vertices->push_back(osg::Vec3(-0.5f, 0.0f, 0.5f));
	osg::ref_ptr<osg::Vec3Array> normals = new osg::Vec3Array;
	normals->push_back(osg::Vec3(0.0f, -1.0f, 0.0f));
	osg::ref_ptr<osg::Vec2Array> texcoords = new osg::Vec2Array;
	texcoords->push_back(osg::Vec2(0.0f, 0.0f));
	texcoords->push_back(osg::Vec2(0.0f, 1.0f));
	texcoords->push_back(osg::Vec2(1.0f, 1.0f));
	texcoords->push_back(osg::Vec2(1.0f, 0.0f));

	// 第四个参数决定透明度，1为完全不透明 0为完全透明
	osg::ref_ptr<osg::Vec4Array> colors = new osg::Vec4Array;
	colors->push_back(osg::Vec4(1.0f, 1.0f, 1.0f, 0.5f));

	osg::ref_ptr<osg::Geometry> quad = new osg::Geometry;
	quad->setVertexArray(vertices.get());
	quad->setNormalArray(normals.get());
	quad->setNormalBinding(osg::Geometry::BIND_OVERALL);
	quad->setColorArray(colors.get());
	quad->setColorBinding(osg::Geometry::BIND_OVERALL);
	quad->setTexCoordArray(0, texcoords.get());
	quad->addPrimitiveSet(new osg::DrawArrays(GL_QUADS, 0, 4));
	osg::ref_ptr<osg::Geode> geode = new osg::Geode;
	geode->addDrawable(quad.get());

	osg::ref_ptr<osg::Texture2D> texture = new osg::Texture2D;
	osg::ref_ptr<osg::Image> image =
		osgDB::readImageFile("Images/lz.rgb");
	texture->setImage(image.get());

	osg::ref_ptr<osg::BlendFunc> blendFunc = new osg::BlendFunc;
	blendFunc->setFunction(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	osg::StateSet* stateset = geode->getOrCreateStateSet();
	stateset->setTextureAttributeAndModes(0, texture.get());
	stateset->setAttributeAndModes(blendFunc);
	stateset->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);

	osg::ref_ptr<osg::Group> root = new osg::Group;
	root->addChild(geode.get());
	root->addChild(osgDB::readNodeFile("glider.osg"));
	osgViewer::Viewer viewer;
	viewer.setSceneData(root.get());
	return viewer.run();
}
/*
stateset->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);这行代码和四边形的透明度有直接关系。
这行代码是设置状态集（StateSet）的渲染提示为TRANSPARENT_BIN，这意味着在渲染过程中，
OSG会将这个状态集中的对象视为透明对象，并在渲染其他不透明对象之后再进行渲染。
当场景中存在透明或半透明的对象时，渲染的顺序就变得非常重要。
因为在计算像素颜色时，需要考虑到从相机到该像素经过的所有物体的颜色和透明度。
通常，我们需要先渲染不透明的物体，然后再按照从远到近的顺序渲染透明的物体。
这样才能正确地计算出每个像素的颜色。
所以，stateset->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
这行代码就是用来控制渲染的顺序，以便正确地处理透明和半透明的对象
*/