using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using OpenTK.Graphics;
using OpenTK.Graphics.OpenGL;

namespace OpenTK.Object
{
    public class Face
    {
        /// <summary>
        /// Indices the los vertices
        /// </summary>
        public int[] VerticesIndices = new int[3];

        /// <summary>
        /// Indices the los vertices
        /// </summary>
        public int[] NormalsIndices = new int[3];
    }

    class Mesh
    {
        #region Properties

        /// <summary>
        /// Lista de poligonos [Triangulos] del modelo
        /// </summary>
        public List<Face> Faces { set; get; }

        /// <summary>
        /// Lista de vertices
        /// </summary>
        public List<Vector3d> Vertices { set; get; }

        /// <summary>
        /// Lista de vertices
        /// </summary>
        public List<Vector3d> Normals { set; get; }

        #endregion

        #region Constructors

        /// <summary>
        /// The base Constructor.
        /// </summary>
        public Mesh()
        {
            Faces = new List<Face>();
            Vertices = new List<Vector3d>();
            Normals = new List<Vector3d>();
        }

        #endregion

        /// <summary>
        /// Draw the mesh
        /// </summary>
        public void Draw()
        {
            GL.Color4(Color4.White);
            for (int polygons = 0; polygons < Faces.Count; polygons++)
            {
                GL.Begin(BeginMode.Polygon);

                for (int vertexs = 0; vertexs < 3; vertexs++)
                {
                    GL.Normal3(Normals[ Faces[polygons].NormalsIndices[vertexs] ]);
                    GL.Vertex3(Vertices[ Faces[polygons].VerticesIndices[vertexs] ]);
                }

                GL.End();
            }
        }
    }
}
