using System;
using System.Drawing;
using System.Windows.Forms;
using System.Drawing.Imaging;
using OpenTK.Graphics.OpenGL;
using OpenTK.Object;


namespace OpenTK
{
    public partial class OpenTK : Form
    {
        #region Members

        /// <summary>
        /// Off loader
        /// </summary>
        OffLoader _offloader;

        /// <summary>
        /// Object mesh
        /// </summary>
        private Mesh _objectMesh;

        #endregion

        public OpenTK()
        {
            InitializeComponent();
        }

        #region GL Control

        /**OPENGL**/
        private void GLC_display_Load(object sender, EventArgs e)
        {
            //CONTEXT
            GL.ClearColor(Color.Black);
            GL.Enable(EnableCap.DepthTest);
            //GL.Enable(EnableCap.CullFace);
            GL.CullFace(CullFaceMode.Back);

            GL.Enable(EnableCap.Blend);
            GL.BlendFunc(BlendingFactorSrc.SrcAlpha, BlendingFactorDest.OneMinusSrcAlpha);

            SetupViewport();
            
            //Models
            //_offloader = new OffLoader(@"..\..\Files\2Triangles.off");

            if(!ObjectLoader.GetMesh(@"..\..\Files\SphereC4D.obj", out _objectMesh))
                Console.WriteLine("The file is Invalid");
        }

        private void SetupViewport()
        {

            float aspectRatio = (float)GLC_display.Width / GLC_display.Height;

            GL.Viewport(0, 0, GLC_display.Width, GLC_display.Height);
            GL.MatrixMode(MatrixMode.Projection);
            GL.LoadIdentity();

            Matrix4 perspective = Matrix4.CreatePerspectiveFieldOfView((float)(Math.PI / 4f), aspectRatio, 0.01f, 2000f);
            GL.MultMatrix(ref perspective);

            GL.MatrixMode(MatrixMode.Modelview);
            GL.LoadIdentity();
        }

        private void GLC_display_Resize(object sender, EventArgs e)
        {
            SetupViewport();
            GLC_display.Invalidate();
        }

        private void GLC_display_Paint(object sender, PaintEventArgs e)
        {

            GL.Clear(ClearBufferMask.ColorBufferBit | ClearBufferMask.DepthBufferBit);

            Matrix4 lookat = Matrix4.LookAt(Vector3.UnitZ * 500, Vector3.Zero, Vector3.UnitY);
            GL.MatrixMode(MatrixMode.Modelview);
            GL.LoadMatrix(ref lookat);

            GL.PolygonMode(MaterialFace.FrontAndBack, PolygonMode.Point);

            //_offloader.Draw();
            _objectMesh.Draw();

            GLC_display.SwapBuffers();
        }

        #endregion

        #region Textura

        public int LoadTexture(string filename)
        {

            if (String.IsNullOrEmpty(filename)) throw new ArgumentException("The file name can not be empty or null.");

            int id = GL.GenTexture();
            GL.BindTexture(TextureTarget.Texture2D, id);

            //LOAD FILE
            Bitmap image;
            try { image = new Bitmap(filename); }
            catch { Console.WriteLine("ERROR LOAD BITMAP"); return -1; };

            BitmapData imageData = image.LockBits(new Rectangle(0, 0, image.Width, image.Height), ImageLockMode.ReadOnly, System.Drawing.Imaging.PixelFormat.Format32bppRgb);
            GL.TexImage2D(TextureTarget.Texture2D, 0, PixelInternalFormat.Rgb, imageData.Width, imageData.Height, 0, Graphics.OpenGL.PixelFormat.Bgra, PixelType.UnsignedByte, imageData.Scan0);
            image.UnlockBits(imageData);

            //TEXTURE PROPERTY
            GL.TexParameter(TextureTarget.Texture2D, TextureParameterName.TextureMinFilter, (int)TextureMinFilter.Linear);
            GL.TexParameter(TextureTarget.Texture2D, TextureParameterName.TextureMagFilter, (int)TextureMagFilter.Linear);

            return id;
        }

        #endregion
    }    
}
