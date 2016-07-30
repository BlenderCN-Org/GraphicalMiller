# $Id: habugraphics_export.py,v 0.1 2007/01/13 
#------------------------------------------------------------------------
# HabuGraphics exporter for blender 2.63 or above
#
#***************************************************************************//
# HabuGraphics Exporter
#
# Created Jan 13, 2007
# By: Jeremy M Miller
#
# Copyright (c) 2007-2011 Jeremy M Miller, Zachary Irwin.  All rights reserved.
# This source code module, and all information, data, and algorithms
# associated with it, are part of BlueHabu technology (tm).
#
# HabuGraphics Export for Blender 2.63 is free software: you can 
# redistribute it and/or modify it under the terms of the GNU 
# General Public License as published by the Free Software Foundation, 
# either version 3 of the License, or(at your option) any later version.
#
# HabuGraphics Export for Blender 2.63 is distributed in the hope that 
# it will be useful, but WITHOUT ANY WARRANTY; without even the implied 
# warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See 
# the GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with HabuGraphics Export for Blender 2.49.  
# If not, see <http://www.gnu.org/licenses/>.
# 
#***************************************************************************//


#!BPY

#""" Registration info for Blender menus:
#Name: 'HabuGraphics (.hgs)...'
#Blender: 263
#Group: 'Export'
#Tooltip: 'Export to HabuGraphics file (.hgs)'
#"""

#__author__  = ("Jeremy M Miller")
#__email__   = ["Jeremy, info:bluehabu*net"]
#__url__     = ["Author's (Jeremy) homepage, http://dev.bluehabu.com"]
#__version__ = "2007/01/13"
#__bpydoc__ = """\
#This script exports to HabuGraphics format.

#Usage:

#Run this script from "File->Export" menu.  A pop-up will ask whether you
#want to export only selected or all relevant objects.

#Known issues:<br>
#    none;<br>
#"""


bl_info = {
    "name": "HabuGraphcis Scene Format (.x)",
    "author": "Jeremy Miller",
    "version": (0, 0, 1),
    "blender": (2, 6, 3),
    "location": "File > Export > HabuGraphics (.hgs)",
    "description": "Export HabuGraphics Scene Format (.hgs)",
    "warning": "",
    "wiki_url": "http://bluehabu.com",
    "tracker_url": "http://bluehabu.com",
    "category": "Import-Export"}
	

import math
import bpy
from bpy import NMesh, Material, Window, Camera, Object, Scene, Lamp

try:
	from os.path import exists, join
	pytinst = 1
except:
	print "Python not installed, Visit http://www.python.org/ to get python."
	pytinst = 0

def write(filename):
	editmode = Window.EditMode()
	if editmode: Window.EditMode(0)
	print ("Start export")
	out = file(filename, "w")

	for material in Material.get():
		out.write('Material %s\n' % (material.name))
		out.write('Diffuse %f %f %f %f\n' % (material.R, material.G, material.B, material.getTranslucency()))
		out.write('Ambient %f\n' % (material.amb))
		out.write('Specular %f %f %f %f\n' % (material.getSpecCol()[0], material.getSpecCol()[1], material.getSpecCol()[2], material.getSpecTransp())) 

	for object in Blender.Object.Get():
		if(object.getType() == "Mesh"):
			out.write('%s %s\n' % (object.getType(), object.getName()))
			
			mesh_dict = {}
			mesh_dict["verts"] = []
			mesh_dict["indices"] = []
			
			mesh = NMesh.GetRawFromObject(object.name)
			current_verts = mesh.verts[:]          # Save a copy of the vertices
			mesh.transform(object.matrix, 1)      # Convert verts to world space

			for face in mesh.faces:
				for vert in face.v:
					vert_info = []
					
					vert_info.append(vert.co.x)		# record the vert data
					vert_info.append(vert.co.y)
					vert_info.append(vert.co.z)
					
					vert_info.append(vert.no.x)
					vert_info.append(vert.no.y)
					vert_info.append(vert.no.z)
					
					if len(face.uv) > 0:
						vert_info.append(face.uv[face.v.index(vert)][0])
						vert_info.append(face.uv[face.v.index(vert)][1])
					else:
						vert_info.append(0.0)
						vert_info.append(0.0)
					
					if vert_info not in mesh_dict["verts"]:		# if we haven't seen the vert, coords/normal/uv and all, before
						mesh_dict["verts"].append(vert_info)	# add the vert to the list
						
					mesh_dict["indices"].append(mesh_dict["verts"].index(vert_info))	# add our own index (not the blender index) to indices

			out.write('%s\n' % (len(mesh.faces)) )        # Write the number of faces
			out.write('%s\n' % (len(mesh_dict["verts"])) )         # Write the number of vertices
			out.write('%s\n' % (len(mesh_dict["indices"])) )        # Write the number of indices
			
			for material in mesh.materials:
				out.write('Material %s\n' % material.name)

			out.write('Loc %f %f %f\n' % (object.matrixWorld[3][0], object.matrixWorld[3][1], object.matrixWorld[3][2]))

			for vert in mesh_dict["verts"]:					# print verts
				out.write('v %f %f %f ' % (vert[0], vert[1], vert[2]))
				out.write('n %f %f %f ' % (vert[3], vert[4], vert[5]))
				out.write('uv %f %f\n' % (vert[6], vert[7]))

			for index in mesh_dict["indices"]:				# print indices
				out.write('i %i\n' % index)
		
			mesh.verts = current_verts             # Restore the original verts

		elif(object.getType() == "Camera"):
			data = object.data
			cam = Camera.get(data.name)
			out.write('Camera %s\n' % (data.name))
			out.write('Right %f %f %f\n' %   (object.getMatrix()[0][0], object.getMatrix()[0][1],  object.getMatrix()[0][2]))
			out.write('Up %f %f %f\n' %      (object.getMatrix()[1][0], object.getMatrix()[1][1],  object.getMatrix()[1][2]))
			out.write('Forward %f %f %f\n' % (object.getMatrix()[2][0], object.getMatrix()[2][1],  object.getMatrix()[2][2]))
			out.write('Loc %f %f %f\n' %     (object.getLocation()[0],  object.getLocation()[1],   object.getLocation()[2]))
			out.write('Far %f\n' %           (cam.getClipEnd()))
			out.write('Near %f\n' %          (cam.getClipStart()))
			out.write('FOV %f\n' %           (2.0 * math.atan(16.0/cam.getLens())))
			
		elif object.getType() == "Lamp":
			data = object.data
			light = Lamp.get(data.name)
			if light.type == Lamp.Types.Lamp:
				out.write('Light Default\n')
				out.write('Type Omni\n')
				out.write('Color 1.0 1.0 1.0\n')
				out.write('Right 1.0 0.0 0.0\n')
				out.write('Up 0.0 1.0 0.0\n')
				out.write('Forward 0.0 0.0 1.0\n')
				out.write('Loc 0.0 20.0 0.0\n')
			elif light.type == Lamp.Types.Spot:
				out.write('Light Default\n')
				out.write('Type Omni\n')
				out.write('Color 1.0 1.0 1.0\n')
				out.write('Right 1.0 0.0 0.0\n')
				out.write('Up 0.0 1.0 0.0\n')
				out.write('Forward 0.0 0.0 1.0\n')
				out.write('Loc 0.0 20.0 0.0\n')
			elif light.type == Lamp.Types.Sun:
				out.write('Light %s\n' % (data.name))
				out.write('Type Omni\n')
				out.write('Color %f %f %f\n' % (light.R, light.G, light.B))
				out.write('Right %f %f %f\n' %   (object.getMatrix()[0][0], object.getMatrix()[0][1],  object.getMatrix()[0][2]))
				out.write('Up %f %f %f\n' %      (object.getMatrix()[1][0], object.getMatrix()[1][1],  object.getMatrix()[1][2]))
				out.write('Forward %f %f %f\n' % (object.getMatrix()[2][0], object.getMatrix()[2][1],  object.getMatrix()[2][2]))
				out.write('Loc %f %f %f\n' %     (object.matrixWorld[3][0], object.matrixWorld[3][1], object.matrixWorld[3][2]))
			else:
				out.write('Light Default\n')
				out.write('Type Omni\n')
				out.write('Color 1.0 1.0 1.0\n')
				out.write('Right 1.0 0.0 0.0\n')
				out.write('Up 0.0 1.0 0.0\n')
				out.write('Forward 0.0 0.0 1.0\n')
				out.write('Loc 0.0 20.0 0.0\n')

	out.close()
	print "End export"

Blender.Window.FileSelector(write, "Export")
