namespace OpenTK
{
    partial class OpenTK
    {
        /// <summary>
        /// Variable del diseñador requerida.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Limpiar los recursos que se estén utilizando.
        /// </summary>
        /// <param name="disposing">true si los recursos administrados se deben eliminar; false en caso contrario, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Código generado por el Diseñador de Windows Forms

        /// <summary>
        /// Método necesario para admitir el Diseñador. No se puede modificar
        /// el contenido del método con el editor de código.
        /// </summary>
        private void InitializeComponent()
        {
            this.GLC_display = new GLControl();
            this.SuspendLayout();

            // 
            // GLC_display
            // 
            this.GLC_display.BackColor = System.Drawing.Color.Black;
            this.GLC_display.Dock = System.Windows.Forms.DockStyle.Fill;
            this.GLC_display.Location = new System.Drawing.Point(0, 0);
            this.GLC_display.Name = "GLC_display";
            this.GLC_display.Size = new System.Drawing.Size(991, 586);
            this.GLC_display.TabIndex = 0;
            this.GLC_display.VSync = false;
            this.GLC_display.Load += new System.EventHandler(this.GLC_display_Load);
            this.GLC_display.Paint += new System.Windows.Forms.PaintEventHandler(this.GLC_display_Paint);
            this.GLC_display.Resize += new System.EventHandler(this.GLC_display_Resize);
            // 
            // OpenTK
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(991, 586);
            this.Controls.Add(this.GLC_display);
            this.Name = "OpenTK";
            this.Text = "OpenTK - WidgetPC";
            this.ResumeLayout(false);

        }

        #endregion

        private GLControl GLC_display;
    }
}

