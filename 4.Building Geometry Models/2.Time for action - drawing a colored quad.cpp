#include <osg/Geometry>
#include <osg/Geode>
#include <osgViewer/Viewer>

int main()
{
	// 顶点
	osg::ref_ptr<osg::Vec3Array> vertices = new osg::Vec3Array;
	vertices->push_back(osg::Vec3(0.0f, 0.0f, 0.0f));
	vertices->push_back(osg::Vec3(1.0f, 0.0f, 0.0f));
	vertices->push_back(osg::Vec3(1.0f, 0.0f, 1.0f));
	vertices->push_back(osg::Vec3(0.0f, 0.0f, 1.0f));

	// 法线
	osg::ref_ptr<osg::Vec3Array> normals = new osg::Vec3Array;
	normals->push_back(osg::Vec3(0.0f, -1.0f, 0.0f));

	// 顶点颜色
	osg::ref_ptr<osg::Vec4Array> colors = new osg::Vec4Array;
	colors->push_back(osg::Vec4(1.0f, 0.0f, 0.0f, 1.0f));
	colors->push_back(osg::Vec4(0.0f, 1.0f, 0.0f, 1.0f));
	colors->push_back(osg::Vec4(0.0f, 0.0f, 1.0f, 1.0f));
	colors->push_back(osg::Vec4(1.0f, 1.0f, 1.0f, 1.0f));

	// 存储不同的数组类型
	// 管理一个几何基元数据来按照顺序方式渲染
	osg::ref_ptr<osg::Geometry> quad = new osg::Geometry;
	quad->setVertexArray(vertices.get());
	quad->setNormalArray(normals.get());
	quad->setNormalBinding(osg::Geometry::BIND_OVERALL);		//单一的法线绑定到整个几何体
	quad->setColorArray(colors.get());
	quad->setColorBinding(osg::Geometry::BIND_PER_VERTEX);		//颜色绑定到每个顶点

	// 指定基元集合，绘制模式为四边形
	quad->addPrimitiveSet(new osg::DrawArrays(GL_QUADS, 0, 4));

	osg::ref_ptr<osg::Geode> root = new osg::Geode;
	root->addDrawable(quad.get());
	osgViewer::Viewer viewer;
	viewer.setSceneData(root.get());
	return viewer.run();
}

// 备注
// 如果quad->setColorBinding(osg::Geometry::BIND_PER_VERTEX);改为BIND_OVERALL
// 则生成的四边形为红色，原因是这时候不再一个顶点对应一个颜色，而是用第一个顶
// 点的颜色来当做四边形的颜色，而第一个顶点颜色为红色
// 至于为什么只设置了四个顶点颜色，但是四边形中间也有颜色，这是openGl做的颜色插
// 值或者叫颜色混合技术，openGL会自动在这些顶点之间插值颜色，以生成平滑的颜色渐变效果