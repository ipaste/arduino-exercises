import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;

import javax.imageio.ImageIO;


public class BMPHelper {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		testBmp();
	}

	private static void testBmp() {
		File f = new File("sunset.bmp");
		try {
			BufferedImage img = ImageIO.read(f);
			int height = img.getHeight();
			int width = img.getWidth();
			println("Image height*width: " + height + " x " + width);
			
			println("to gray scale:");
			int[][] grayScaleMap = new int[height][width];
			for(int i = 0; i < height; i++) {
				for(int j = 0; j < width; j++) {
					int pixel = img.getRGB(i,  j);
					int r = pixel & 0x00FF0000 >> 16;
					int g = pixel & 0x0000FF00 >> 8;
					int b = pixel & 0x000000FF;
//					System.out.print("0x"+ String.format("%02x", toGrayScale(r, g, b)));
					System.out.print("0x"+ String.format("%02x", toGrayScale(r, g, b)));
					grayScaleMap[i][j] =  toGrayScale(r, g, b);
					if(j != width - 1)
						System.out.print(", ");
					else
						System.out.println();
				}
			}
			
			println("to 4 bit(16 color):");
			char[][] bitMap = new char[height][width/2];
			for(int i = 0; i < height; i++) {
				for(int j = 0; j < width - 1; j+=2) {
					char h = (char) (grayScaleMap[i][j] / 16 << 4);
					char l = (char) (grayScaleMap[i][j + 1]/16);
					char color = (char) (h | l);
					System.out.print(String.format("0x%02x", (int)color));
					if(j != width - 1)
						System.out.print(", ");
					
					// set to the bitmap array
					bitMap[i][j/2] = color;
				}
				println("");
			}
			
			println("to 2 bit(4 color):");
			char[][] bitmap4L = new char[height][width/4];
			for(int i = 0; i < height; i++) {
				for(int j = 0; j < width - 1; j+=4) {
					char hh = (char) (grayScaleMap[i][j] / 64 << 6);
					char hl = (char) (grayScaleMap[i][j + 1] / 64 << 4);
					char lh = (char) (grayScaleMap[i][j + 2] / 64 << 2);
					char ll = (char) (grayScaleMap[i][j + 3]/64);
					char color = (char) (hh | hl | lh | ll);
					System.out.print(String.format("0x%02x", (int)color));
					if(j != width - 1)
						System.out.print(", ");
					
					// set to the bitmap array
					bitmap4L[i][j/4] = color;
				}
				println("");
			}
			
			println("to specific array size(96x96):");
			
				
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}

	private static void println(String string) {
		// TODO Auto-generated method stub
		System.out.println(string);
	}

	private static int toGrayScale(int red, int green, int blue) {
		return (int)(red * 0.3f + green * 0.6f + blue * 0.1f);
	}
	
	
}
