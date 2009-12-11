/***************************************************************************
 *   Copyright (C) 2008-2009 by Andrzej Rybczak                            *
 *   electricityispower@gmail.com                                          *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA.              *
 ***************************************************************************/

#ifndef _H_MEDIA_LIBRARY
#define _H_MEDIA_LIBRARY

#include "ncmpcpp.h"
#include "screen.h"

class MediaLibrary : public Screen<Window>
{
	struct SearchConstraints
	{
		SearchConstraints(const std::string &artist, const std::string &album, const std::string &year) : Artist(artist), Album(album), Year(year) { }
		SearchConstraints(const std::string &album, const std::string &year) : Album(album), Year(year) { }
		
		std::string Artist;
		std::string Album;
		std::string Year;
	};
	
	public:
		virtual void SwitchTo();
		virtual void Resize();
		
		virtual std::basic_string<my_char_t> Title();
		
		virtual void Refresh();
		virtual void Update();
		
		virtual void EnterPressed() { AddToPlaylist(1); }
		virtual void SpacePressed();
		virtual void MouseButtonPressed(MEVENT);
		virtual bool isTabbable() { return true; }
		
		virtual MPD::Song *CurrentSong();
		
		virtual bool allowsSelection() { return true; }
		virtual void ReverseSelection();
		virtual void GetSelectedSongs(MPD::SongList &);
		
		virtual void ApplyFilter(const std::string &);
		
		virtual List *GetList();
		
		int Columns() { return hasTwoColumns ? 2 : 3; }
		void NextColumn();
		void PrevColumn();
		
		Menu<std::string> *Artists;
		Menu< std::pair<std::string, SearchConstraints> > *Albums;
		Menu<MPD::Song> *Songs;
		
	protected:
		virtual void Init();
		
	private:
		void AddToPlaylist(bool);
		
		static std::string SongToString(const MPD::Song &s, void *);
		
		static bool SortSongsByTrack(MPD::Song *, MPD::Song *);
		static bool SortSongsByYear(MPD::Song *, MPD::Song *);
		
		static bool hasTwoColumns;
		static size_t itsLeftColWidth;
		static size_t itsMiddleColWidth;
		static size_t itsMiddleColStartX;
		static size_t itsRightColWidth;
		static size_t itsRightColStartX;
};

extern MediaLibrary *myLibrary;

#endif

