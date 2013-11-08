using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;

using OpenTK.Graphics;
using OpenTK.Graphics.OpenGL;
using OpenTK;

namespace OpenTK
{
    public class OffLoader
    {
        private int _numOfVertexs, _numOfPolygons;
        private List<Vector3> _vertexs;
        private List<int[]> _polygons;

        /// <summary>
        /// Basic constructor
        /// </summary>
        /// <param name="fileName">Filename of the .off file</param>
        public OffLoader(String fileName)
        {
            //Initialize
            _vertexs = new List<Vector3>();
            _polygons = new List<int[]>();

            string fileToString = GetFileString(fileName);
            if (String.IsNullOrEmpty(fileToString)) throw new ArgumentException("The file name can not be empty or null");

            //Load mesh function
            LoadMesh(fileToString);
        }

        /// <summary>
        /// Load the mesh data
        /// </summary>
        /// <param name="stringMesh">Mesh data in string format</param>
        private void LoadMesh(String stringMesh)
        {
            using (StringReader reader = new StringReader(stringMesh))
            {
                string line;
                int materialIndex = -1, lines = 0;

                while ((line = reader.ReadLine()) != null)
                {
                    //Local update
                    line = line.Replace('.', ',');
                    lines++;

                    //Evaluate the format
                    if (lines == 1)
                    {
                        if (line != "OFF")
                            throw new ArgumentException("File's format invalid", line);
                        else
                            continue;
                    }

                    //Read number of vertexs and polygons
                    else if (lines == 2)
                    {
                        string[] dataCounter = line.Split(' ');
                        try
                        {
                            if (dataCounter.Length != 3)
                                throw new ArgumentException("Invalid data's format", line);

                            _numOfVertexs = int.Parse(dataCounter[0]);
                            _numOfPolygons = int.Parse(dataCounter[1]);
                        }
                        catch
                        {
                            throw new ArgumentException("Invalid data's counter", line);
                        }
                    }

                    //Save all vertexs
                    else if (lines - 2 <= _numOfVertexs)
                    {
                        string[] dataCounter = line.Split(' ');

                        try
                        {
                            if (dataCounter.Length != 3)
                                throw new ArgumentException("Invalid data's format", line);

                            _vertexs.Add(new Vector3(float.Parse(dataCounter[0]), float.Parse(dataCounter[1]), float.Parse(dataCounter[2])));
                        }
                        catch
                        {
                            throw new ArgumentException("Invalid data's counter", line);
                        }
                    }

                    //Save all polygons
                    else if (lines - 2 <= _numOfVertexs + _numOfPolygons)
                    {
                        string[] dataCounter = line.Split(' ');

                        try
                        {
                            if (dataCounter.Length < 4)
                                throw new ArgumentException("Invalid data's format", line);

                            int numerOfVertexs = int.Parse(dataCounter[0]);
                            int[] vertexsIndexArray = new int[numerOfVertexs];

                            for (int index = 0; index < numerOfVertexs; index++)
                            {
                                vertexsIndexArray[index] = int.Parse(dataCounter[index + 1]);
                            }

                            _polygons.Add(vertexsIndexArray);
                        }
                        catch
                        {
                            throw new ArgumentException("Invalid data's counter", line);
                        }
                    }
                }
            }
        }

        /// <summary>
        /// Draw the mesh
        /// </summary>
        public void Draw()
        {
            GL.Color4(Color4.White);
            for (int polygons = 0; polygons < _polygons.Count; polygons++)
            {
                GL.Begin(BeginMode.Polygon);

                for (int vertexs = 0; vertexs < _polygons[polygons].Length; vertexs++)
                    GL.Vertex3(_vertexs[_polygons[polygons][vertexs]]);
                
                GL.End();
            }
        }

        /// <summary>
        /// Put the file's data into a string
        /// </summary>
        /// <param name="fileName">Filename of the .off file</param>
        /// <returns>File's data</returns>
        private string GetFileString(string fileName)
        {
            try
            {
                StreamReader file = new StreamReader(fileName);
                string fileSTR = file.ReadToEnd();
                file.Close();
                return fileSTR;
            }
            catch { Console.Write("ERROR FILE"); }
            return "";
        }
    }
}
