using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;

namespace OpenTK.Object
{
    class ObjectLoader
    {
        /// <summary>
        /// Create the object mesh
        /// </summary>
        /// <param name="fileName">Filename of the object model</param>
        /// <param name="mesh">Reference to the mesh</param>
        /// <returns>Load status</returns>
        public static bool GetMesh(string fileName, out Mesh mesh)
        {
            mesh = new Mesh();

            var fileToString = GetFileString(fileName);
            if (String.IsNullOrEmpty(fileToString))
            {
                Console.WriteLine("The file name can not be empty or null");
                return false;
            }

            using (var reader = new StringReader(fileToString))
            {

                string line;
                var initRead = true;
                var materialIndex = -1;

                while ((line = reader.ReadLine()) != null)
                {
                    //#: representa comentarios dentro del archivo
                    if (line.Length > 0 && line.ElementAt(0) != '#')
                    {
                        string[] split;
                        switch (line.ElementAt(0))
                        {
                            #region VERTEX

                            case 'v':

                                //UPDATE STRING NUMBERS
                                line = line.Replace('.', ',');
                                int space;
                                var value = Vector3d.Zero;

                                for (space = 1; space < line.Length; space++)
                                    if (!line.ElementAt(space).Equals(' ')) break;

                                split = line.Substring(space, line.Length - space).Split(' ');
                                switch (line.ElementAt(1))
                                {
                                    //VERTEX RECORDING
                                    case ' ':
                                        if (double.TryParse(split[0], out value.X) && double.TryParse(split[1], out value.Y) && double.TryParse(split[2], out value.Z))
                                        {
                                            mesh.Vertices.Add(value);
                                        }
                                        break;

                                    //NORMAL RECORING
                                    case 'n':
                                            if (double.TryParse(split[1], out value.X) && double.TryParse(split[2], out value.Y) && double.TryParse(split[3], out value.Z))
                                            {
                                                mesh.Normals.Add(value);
                                            }
                                        break;
                                }

                                break;
                                
                            #endregion

                            #region FACE AND LINE

                            case 'f':

                                //ORDEN BY FACE - VERTEX / TEXTURE / NORMAL

                                //FACE RECORDING
                                var currentsIndexs = line.Substring(2, line.Length - 2).Split(' ');
                                var currentFace = new Face();

                                //EVALUETE EAXH VERTEX
                                var index = 0;
                                foreach (var vertex in currentsIndexs)
                                {
                                    if (index >= 3)
                                        throw new ArgumentNullException("the polygon can have a maximum of 3 vertices [triangle]");

                                    var indices = vertex.Split('/');
                                    int currentIndex;

                                    //Vertex
                                    if (int.TryParse(indices[0], out currentIndex))
                                        currentFace.VerticesIndices[index] = currentIndex - 1;

                                    //Normal
                                    if (int.TryParse(indices[2], out currentIndex))
                                        currentFace.NormalsIndices[index] = currentIndex - 1;

                                    index++;
                                }

                                if(index < 3)
                                    throw new ArgumentNullException("Number of vertices is invalid");

                                mesh.Faces.Add(currentFace);

                                break;
                                
                            #endregion
                        }
                    }
                }
            }

            return true;
        }

        /// <summary>
        /// Transfiere un archivo completo a un string
        /// </summary>
        /// <param name="fileName">Archivo a cargar</param>
        /// <returns>Archivo en el string</returns>
        static public string GetFileString(string fileName)
        {
            try
            {
                var file = new StreamReader(fileName);
                var fileSTR = file.ReadToEnd();
                file.Close();
                return fileSTR;
            }
            catch { Console.Write("ERROR FILE"); }
            return "";
        }
    }
}
