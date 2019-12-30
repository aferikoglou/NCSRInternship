# Import system modules
import sys
import os
import shutil

from PIL import Image
import glob

base_dir = sys.argv[1] 
simulation = sys.argv[2]
path_to_sim_out_dir = base_dir + '//' + simulation

def gif_gen():
    frames = []
    imgs = glob.glob(path_to_sim_out_dir + "//POT_IT_*.png")
    for img in sorted(imgs):
        frame = Image.open(img)
        frames.append(frame)
    frames[0].save(path_to_sim_out_dir + '//POT_GIF.gif', format='GIF', append_images=frames[1:], save_all=True, duration=100, loop=0)


def png_gen():
    for filename in os.listdir(path_to_sim_out_dir):
        if filename.startswith("POT_IT"):
            # Get current iteration
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


def main():
    # Create potential, mean phase velocity and mean phase velocity horizontal cut pngs
    png_gen()
    # Create potential gif
    gif_gen()

if __name__ == "__main__":
    main()