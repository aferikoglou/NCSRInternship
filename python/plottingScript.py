import sys
import os
import shutil
import argparse

from PIL import Image
import glob

##### Helping functions #####

def gif_gen(path_to_sim_out_dir):
    frames = []
    imgs = glob.glob(path_to_sim_out_dir + "//POT_IT_*.png")
    for img in sorted(imgs):
        frame = Image.open(img)
        frames.append(frame)
    frames[0].save(path_to_sim_out_dir + '//POT_GIF.gif', format='GIF', append_images=frames[1:], save_all=True, duration=100, loop=0)


def png_gen(base_dir, simulation, path_to_sim_out_dir):
    for filename in os.listdir(path_to_sim_out_dir):
        if filename.startswith("POT_IT"):
            parts = filename.split("_")
            it = parts[2].split(".")[0]
            command = """ gnuplot -e "set terminal png size 500,500 ; set output '""" + base_dir + """/""" + simulation + """/POT_IT_""" + it + """.png' ; set title 'Potential' ; set xlabel 'i' ; set xrange [-0.5:29.5] ; set ylabel 'j' ; set yrange [-0.5:29.5] ; set cbrange [-2.2:2.2] ;  plot [][] '""" + base_dir + """/""" + simulation + """/POT_IT_""" + it + """.dat' using 1:2:3 with image notitle" """
            os.system(command)
        elif filename.startswith("MPV_HORCUT"):
            command = """ gnuplot -e "set terminal png size 500,500 ; set output '""" + base_dir + """/""" + simulation + """/MPV_HORCUT.png' ; set title 'Mean Phase Velocity Horizontal Cut' ; set xlabel 'i' ; set xrange [-0.5:29.5] ; set ylabel 'Mean Phase Velocity' ;  plot '""" + base_dir + """/""" + simulation + """/MPV_HORCUT.dat' using 1:2 pointtype 7 notitle" """
            os.system(command)
        elif filename.startswith("MPV"):
            command = """ gnuplot -e "set terminal png size 500,500 ; set output '""" + base_dir + """/""" + simulation + """/MPV.png' ; set title 'Mean Phase Velocity' ; set xlabel 'i' ; set xrange [-0.5:29.5] ; set ylabel 'j' ; set yrange [-0.5:29.5] ; plot [][] '""" + base_dir + """/""" + simulation + """/MPV.dat' using 1:2:3 with image notitle" """
            os.system(command)

##### Main script #####

##### Parse command line arguments #####
parser = argparse.ArgumentParser(description='A script that creates the potential, mean phase velocity, mean phase velocity horizontal cut .png files and the potential .gif file.')
parser.add_argument('--BASE_DIR', type=str, required=True, help='The directory in which the simulation directory is found.')
parser.add_argument('--SIMULATION', type=str, required=True, help='The simulation name.')
 
args = parser.parse_args()
 
base_dir   = args.BASE_DIR
simulation = args.SIMULATION

path_to_sim_out_dir = base_dir + '//' + simulation # base_dir + '//' + simulation For Windows

##### Create potential, mean phase velocity and mean phase velocity horizontal cut .png files #####
png_gen(base_dir, simulation, path_to_sim_out_dir)

##### Create potential .gif file #####
gif_gen(path_to_sim_out_dir)

