using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Windows.Forms.DataVisualization.Charting;
using System.IO;
using MathNet.Numerics.LinearAlgebra;
using MathNet.Numerics.LinearAlgebra.Double;

namespace LabWork1
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
            timer.Tick += Timer_Tick;

            chart1.Series.Add(0.ToString());
            chart1.Series[0.ToString()].ChartType = System.Windows.Forms.DataVisualization.Charting.SeriesChartType.FastPoint;
            chart1.Series[0.ToString()].Color = Color.Black;
            chart1.Series[0.ToString()].MarkerStyle = MarkerStyle.Star6;
            chart1.Series[0.ToString()].MarkerSize = 20;
        }
        int r;
        int j = 1;
        char flagg = 'o';
        private Timer timer = new Timer();
        uint timer_count = 0;
        TMyRK task;
        double h;







        private void Form1_Load(object sender, EventArgs e)
        {

            //chart1.ChartAreas[0].AxisX.MajorGrid.Enabled = false;
            //chart1.ChartAreas[0].AxisY.MajorGrid.Enabled = false;
            //chart1.ChartAreas[0].AxisX.ScaleView.Zoom(-Math.PI, Math.PI);
            chart1.ChartAreas[0].CursorX.IsUserEnabled = true;
            chart1.ChartAreas[0].CursorX.IsUserSelectionEnabled = true;

            /*          chart1.ChartAreas[0].AxisX.ScrollBar.IsPositionedInside = true;*/
            chart1.ChartAreas[0].AxisX.MajorGrid.LineColor = Color.LightGray;
            chart1.ChartAreas[0].AxisY.MajorGrid.LineColor = Color.LightGray;
            chart1.ChartAreas[0].AxisX.ScaleView.Zoomable = true;
            chart1.ChartAreas[0].AxisX.Interval = 1;
            chart1.ChartAreas[0].AxisY.Interval = 1;
            chart1.ChartAreas[0].CursorY.IsUserEnabled = true;
            chart1.ChartAreas[0].CursorY.IsUserSelectionEnabled = true;
            chart1.ChartAreas[0].AxisY.ScaleView.Zoomable = true;
            //chart1.ChartAreas[0].AxisY.ScrollBar.IsPositionedInside = true;
            chart1.ChartAreas[0].AxisX.Minimum = 0;
            chart1.ChartAreas[0].AxisX.Maximum = 2 * Math.PI;
            chart1.ChartAreas[0].AxisY.Minimum = 0;
            chart1.ChartAreas[0].AxisY.Maximum = 2 * Math.PI;
            chart1.ChartAreas[0].AxisX.Title = "phi_1";
            chart1.ChartAreas[0].AxisY.Title = "phi_2";

        }




        private void button_clear_gr_Click(object sender, EventArgs e)
        {
            chart1.Series.Clear();
            chart1.Legends.Clear();
            timer.Enabled = false;
            chart1.Series.Add(0.ToString());
            chart1.Series[0.ToString()].ChartType = System.Windows.Forms.DataVisualization.Charting.SeriesChartType.FastPoint;
            chart1.Series[0.ToString()].Color = Color.Black;
            chart1.Series[0.ToString()].MarkerStyle = MarkerStyle.Star6;
            chart1.Series[0.ToString()].MarkerSize = 20;
        }




        private void textBox_h_KeyPress(object sender, KeyPressEventArgs e)
        {
            char ch = e.KeyChar;
            if (!Char.IsDigit(ch) && ch != 8 && (ch != ',' || textBox_h.Text.Contains(",")))
            {
                e.Handled = true;
            }
        }

        private void textBox_ε_KeyPress(object sender, KeyPressEventArgs e)
        {
            char ch = e.KeyChar;

            e.Handled = true;

        }

        private void textBox_eps_gran_KeyPress(object sender, KeyPressEventArgs e)
        {
            char ch = e.KeyChar;
            if (!Char.IsDigit(ch) && ch != 8 && (ch != ',' || textBox_eps_gran.Text.Contains(","))) //глянуть видео и доделать
            {
                e.Handled = true;
            }
        }




        private void textBox_tf_KeyPress(object sender, KeyPressEventArgs e)
        {
            char ch = e.KeyChar;
            if (!Char.IsDigit(ch) && ch != 8 && (ch != ',' || textBox_tf.Text.Contains(","))) //глянуть видео и доделать
            {
                e.Handled = true;
            }
        }


        private void textBox_max_n_KeyPress(object sender, KeyPressEventArgs e)
        {
            char ch = e.KeyChar;

            e.Handled = true;

        }










        private void Timer_Tick(object sender, EventArgs e)
        {
            //if (MaxX_end < MaxX)
            //{
            //    MaxX_end += InterpolationStep;
            //    Invalidate();
            //}
            //else
            //{
            //    MaxX_end = MaxX;
            //    Invalidate();
            //    timer.Enabled = false;
            //}
            int n = 5;
            n = trackBar_speed.Value;
            for (int i = 0; i < n; i++)
            {
                if (task.XY[1, 0] > 2 * Math.PI || task.XY[0, 0] > 2 * Math.PI || task.XY[0, 0] < 0 || task.XY[1, 0] < 0)
                {
                    if (task.XY[1, 0] > 2 * Math.PI)
                    {
                        flagg = 't';
                        task.XY[1, 0] = 0;
                    }
                    else if (task.XY[0, 0] > 2 * Math.PI)
                    {
                        flagg = 'r';
                        task.XY[0, 0] = 0;
                    }
                    else if (task.XY[0, 0] < 0)
                    {
                        flagg = 'b';
                        task.XY[0, 0] = 2 * Math.PI;
                    }
                    else if (task.XY[1, 0] < 0)
                    {
                        flagg = 'l';
                        task.XY[1, 0] = 2 * Math.PI;
                    }
                }
                //else
                //{
                //int s = j;
                double X_prev = task.XY[0, 0];
                double Y_prev = task.XY[1, 0];
                int j = chart1.Series.Count;
                if (r == 0)

                {
                    chart1.Series[(j - 1).ToString()].Points.AddXY(task.XY[0, 0], task.XY[1, 0]);
                }
                else
                if (r == 1)
                {
                    chart1.Series[(j - 1).ToString()].Points.AddXY(task.t, task.XY[0, 0]);
                }
                else
                if (r == 2)
                {
                    chart1.Series[(j - 1).ToString()].Points.AddXY(task.t, task.XY[1, 0]);
                }
                string ss = "(" + Math.Round(task.XY[0, 0], 2, MidpointRounding.AwayFromZero).ToString() + "; " + Math.Round(task.XY[1, 0], 2, MidpointRounding.AwayFromZero).ToString() + ")";
                textBox_last_point.Text = ss;
                task.NextStep(h);
                if (r == 0)

                {
                    chart1.Series[0.ToString()].Points.Clear();
                    chart1.Series[0.ToString()].Points.AddXY(task.XY[0, 0], task.XY[1, 0]);
                }

            }


            //chart1.Series[0].Points.AddXY(1, timer_count/100.0);
            //Console.WriteLine(timer_count);
            timer_count++;


        }

        private void button_traj_Click(object sender, EventArgs e)
        {
            double phi1 = Convert.ToDouble(textBox_phi1.Text.ToString());
            double phi2 = Convert.ToDouble(textBox_phi2.Text.ToString());
            double gamma = Convert.ToDouble(textBox_gamma.Text.ToString());
            h = Convert.ToDouble(textBox_h.Text.ToString());
            double tfinal = Convert.ToDouble(textBox_tf.Text.ToString());
            double eps_gran = Convert.ToDouble(textBox_eps_gran.Text.ToString());
            double d = Convert.ToDouble(textBox_d.Text.ToString());
            double sigma = Convert.ToDouble(textBox_sigma.Text.ToString());
            r = 0;
            int j = chart1.Series.Count;
            chart1.Series.Insert(j - 1, new Series(j.ToString()));
            chart1.Series[j.ToString()].ChartType = System.Windows.Forms.DataVisualization.Charting.SeriesChartType.FastPoint;
            chart1.Legends.Add(j.ToString());
            string ss = "(" + phi1.ToString() + "," + phi2.ToString() + ")";
            chart1.Series[j.ToString()].LegendText = ss;
            chart1.Series[j.ToString()].MarkerSize = 2;
            //var name = chart1.Series.FindByName(0.ToString());
            //if (name != null)
            //{
            //    chart1.Series.Remove(name);
            //}
            task = new TMyRK(gamma, d, sigma, 1);
            Matrix<double> XY0 = Matrix<double>.Build.Dense(2, 1);
            XY0[0, 0] = phi1;
            XY0[1, 0] = phi2;
            task.SetInit(0, XY0);

            timer.Interval = 1;
            timer.Enabled = true;








            //chart1.Series.Add(j.ToString());
            //chart1.Series[j.ToString()].ChartType = System.Windows.Forms.DataVisualization.Charting.SeriesChartType.FastPoint;

            //DrawLine(gamma, d, sigma, phi1, phi2, h, tfinal, eps_gran, j.ToString());



            updateStripLines();
        }



        private void button_stop_Click(object sender, EventArgs e)
        {
            timer.Enabled = false;
        }

        private void button1_Click(object sender, EventArgs e)
        {
            /*
            double gamma = Convert.ToDouble(textBox_gamma.Text.ToString());

            double d = Convert.ToDouble(textBox_d.Text.ToString());
            double sigma = Convert.ToDouble(textBox_sigma.Text.ToString());

            chart1.Series.Add(j.ToString());
            chart1.Series[j.ToString()].ChartType = System.Windows.Forms.DataVisualization.Charting.SeriesChartType.FastPoint;
            chart1.Series[j.ToString()].MarkerSize = 4;
            chart1.Series[j.ToString()].Color = Color.Green;
            chart1.Series[j.ToString()].MarkerStyle = MarkerStyle.Square;
            chart1.Legends.Add(j.ToString());
            string s = "-";
            chart1.Series[j.ToString()].LegendText = s;
            double p = Math.Asin(gamma - d);
            for (double k = 0; k < 2 * Math.PI; k = k + 0.01)
            {
                if (Math.PI / 2 - sigma > 0)
                {
                    for (double l = Math.PI / 2 - sigma; l < Math.PI / 2 + sigma; l = l + 0.01)
                    {
                        chart1.Series[j.ToString()].Points.AddXY(k, l);
                    }
                }
                else
                {
                    for (double l = 0; l < Math.PI / 2 + sigma; l = l + 0.01)
                    {
                        chart1.Series[j.ToString()].Points.AddXY(k, l);
                    }
                    for (double l = 2 * Math.PI - sigma + Math.PI / 2; l < 2 * Math.PI; l = l + 0.01)
                    {
                        chart1.Series[j.ToString()].Points.AddXY(k, l);
                    }
                }
            }
            j++;
            if (d <= 2.01 && d >= 0.01)
            {
                chart1.Series.Add(j.ToString());
                chart1.Series[j.ToString()].ChartType = System.Windows.Forms.DataVisualization.Charting.SeriesChartType.FastPoint;
                chart1.Series[j.ToString()].MarkerSize = 2;
                chart1.Series[j.ToString()].Color = Color.Black;
                chart1.Legends.Add(j.ToString());
                s = "-";
                chart1.Series[j.ToString()].LegendText = s;
                j++;
                chart1.Series.Add(j.ToString());
                chart1.Series[j.ToString()].ChartType = System.Windows.Forms.DataVisualization.Charting.SeriesChartType.FastPoint;
                chart1.Series[j.ToString()].MarkerSize = 2;
                chart1.Series[j.ToString()].Color = Color.Black;


                for (double i = 0; i < 2 * Math.PI; i = i + 0.01)
                {
                    if (Math.PI / 2 - sigma > 0)
                    {
                        if (i > Math.PI / 2 + sigma || i < Math.PI / 2 - sigma)
                        {
                            if (p >= 0)
                            {
                                chart1.Series[(j - 1).ToString()].Points.AddXY(p, i);
                            }
                            else
                            {
                                chart1.Series[(j - 1).ToString()].Points.AddXY(2 * Math.PI + p, i);
                            }
                            chart1.Series[j.ToString()].Points.AddXY(Math.PI - p, i);
                        }
                    }
                    else
                        if (Math.PI / 2 - sigma < 0)
                    {
                        if (i > Math.PI / 2 + sigma && i < 2 * Math.PI - sigma + Math.PI / 2)
                        {
                            if (p >= 0)
                            {
                                chart1.Series[(j - 1).ToString()].Points.AddXY(p, i);
                            }
                            else
                            {
                                chart1.Series[(j - 1).ToString()].Points.AddXY(2 * Math.PI + p, i);
                            }
                            chart1.Series[j.ToString()].Points.AddXY(Math.PI - p, i);
                        }
                    }


                }
                chart1.Legends.Add(j.ToString());
                s = "-";
                chart1.Series[j.ToString()].LegendText = s;
            }

            chart1.ChartAreas[0].AxisX.Maximum = 2 * Math.PI;
            chart1.ChartAreas[0].AxisX.Interval = 1;
            j++;
            */
        }

        private void addStripLine(double y1, double y2)
        {
            StripLine stripLine = new StripLine();
            stripLine.Interval = 0;       // Set Strip lines interval to 0 for non periodic stuff
            stripLine.StripWidth = y2 - y1;    // the width of the highlighted area
            stripLine.IntervalOffset = y1;

            stripLine.BackColor = Color.LightSlateGray;
            chart1.ChartAreas[0].AxisY.StripLines.Add(stripLine);
        }

        private void updateStripLines()
        {
            chart1.ChartAreas[0].AxisY.StripLines.Clear();

            if (checkBox1.Checked)
            {
                double sigma = Convert.ToDouble(textBox_sigma.Text.ToString());
                if (Math.PI / 2 - sigma > 0)
                {
                    addStripLine(Math.PI / 2 - sigma, Math.PI / 2 + sigma);
                }
                else
                {
                    addStripLine(0.0, Math.PI / 2 + sigma);
                    addStripLine(Math.PI * 2.5 - sigma, Math.PI * 2.0);
                }
            }
        }

        private void checkBox1_CheckedChanged(object sender, EventArgs e)
        {
            updateStripLines();
        }
    }
}
