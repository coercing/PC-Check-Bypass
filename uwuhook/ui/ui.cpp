//⠀  ⢸⠂⠀⠀⠀⠘⣧⠀⠀⣟⠛⠲⢤⡀⠀⠀⣰⠏⠀⠀⠀⠀⠀⢹⡀
//	⠀⡿⠀⠀⠀⠀⠀⠈⢷⡀⢻⡀⠀⠀⠙⢦⣰⠏⠀⠀⠀⠀⠀⠀⢸⠀
//	⠀⡇⠀⠀⠀⠀⠀⠀⢀⣻⠞⠛⠀⠀⠀⠀⠻⠀⠀⠀⠀⠀⠀⠀⢸⠀
//	⠀⡇⠀⠀⠀⠀⠀⠀⠛⠓⠒⠓⠓⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⠀
//	⠀⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣸⠀              It sucks to say but i am self leaking this source code today
//	⠀⢿⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣀⣀⣀⣀⠀⠀⢀⡟⠀              this project has been sat on my cdn for a long time and lowkey. i wanna self leak it so people can learn from this
//	⠀⠘⣇⠀⠘⣿⠋⢹⠛⣿⡇⠀⠀⠀⠀⣿⣿⡇⠀⢳⠉⠀⣠⡾⠁⠀              Please dont redistribute this source code without giving me credit, i put a lot of work into this and it would be nice to get some recognition for it.
//	⣦⣤⣽⣆⢀⡇⠀⢸⡇⣾⡇⠀⠀⠀⠀⣿⣿⡷⠀⢸⡇⠐⠛⠛⣿               Im just a solo dev after all and i would like to get some recognition for my work, i know this is cringe but hey, i put a lot of work into this and it would be nice to get some recognition for it.
//	⠹⣦⠀⠀⠸⡇⠀⠸⣿⡿⠁⢀⡀⠀⠀⠿⠿⠃⠀⢸⠇⠀⢀⡾⠁
//	⠀⠈⡿⢠⢶⣡⡄⠀⠀⠀⠀⠉⠁⠀⠀⠀⠀⠀⣴⣧⠆⠀⢻⡄                Enjoy the leak chat <3
//	⠀⢸⠃⠀⠘⠉⠀⠀⠀⠠⣄⡴⠲⠶⠴⠃⠀⠀⠀⠉⡀⠀⠀⢻⡄               - ego / @humbleness on discord
//	⠀⠘⠒⠒⠻⢦⣄⡀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣀⣤⠞⠛⠒⠛⠋⠁               https://uwuhook.club
//	⠀⠀⠀⠀⠀⠀⠸⣟⠓⠒⠂⠀⠀⠀⠀⠀⠈⢷⡀
//	⠀⠀⠀⠀⠀⠀⠀⠙⣦⠀⠀⠀⠀⠀⠀⠀⠀⠈⢷⠀⠀⠀⠀⠀⠀
//	⠀⠀⠀⠀⠀⠀⠀⣼⣃⡀⠀⠀⠀⠀⠀⠀⠀⠀⠘⣆⠀⠀⠀⠀⠀⠀
//	⠀⠀⠀⠀⠀⠀⠀⠉⣹⠃⠀⠀⠀⠀⠀⠀⠀⠀⠀⢻⠀⠀⠀⠀⠀⠀
//	⠀⠀⠀⠀⠀⠀⠀⠀⡿⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⡆⠀

#include "ui.hpp"

ImVec2 ui::text_size( fonts_ font, float size, const char* text ) {
    if ( !fonts[font].get( size ) )
        return ImVec2{ 0, 0 };

    return fonts[font].get( size )->CalcTextSizeA( size, FLT_MAX, -1, text, FindRenderedTextEnd( text ) );
}

void ui::add_text( fonts_ font, int size, ImVec2 pos, ImColor col, const char* text, const char* text_end, const ImVec4* cpu_fine_clip_rect ) {
    GetWindowDrawList( )->AddText( fonts[font].get( size ), size, pos, col, text, text_end, 0.f, cpu_fine_clip_rect );
}


void ui::render_page( ) {
	if ( pages.size( ) == 0 || cur_page >= pages.size( ) || pages[cur_page].page == 0 )
        return;

    pages[cur_page].page( );
}

void ui::add_page( int tab_idx, std::function< void( ) > c ) {
	pages[tab_idx].page = c;
}

void ui::page( const page_t& p, bool selected ) {
    auto window = GetCurrentWindow( );
    auto id = window->GetID( p.m_label );

    auto draw = window->DrawList;
    auto pos = window->DC.CursorPos;

    ImRect bb{ pos, { pos.x + CalcItemWidth( ), pos.y + 20 } };
    ItemAdd( bb, id );
    ItemSize( bb );

    window->DrawList->AddRectFilledMultiColor( bb.Min, bb.Max, GetColorU32( ImGuiCol_Border, 0.25f ), GetColorU32( ImGuiCol_Border, 0.f ), GetColorU32( ImGuiCol_Border, 0.f ), GetColorU32( ImGuiCol_Border, 0.25f ) );
    window->DrawList->AddLine( bb.Min, { bb.Min.x, bb.Max.y }, GetColorU32( ImGuiCol_Scheme, selected ? 1.f : 0.25f ) );
    add_text( font, 13, { bb.Min.x + 8, bb.GetCenter( ).y - 13 / 2 - 1 }, GetColorU32( selected ? ImGuiCol_Scheme : ImGuiCol_TextDisabled ), p.m_label, FindRenderedTextEnd( p.m_label ) );
}

void ui::begin_child( const char* label, ImVec2 size ) {
    BeginChild( std::string( label ).append( "decor" ).c_str( ), CalcItemSize( size, GetWindowWidth( ), GetWindowHeight( ) ), ImGuiWindowFlags_NoScrollbar );
    GetWindowDrawList( )->AddRectFilledMultiColor( { GetWindowPos( ).x + 1, GetWindowPos( ).y + 1 }, { GetWindowPos( ).x + GetWindowWidth( ) - 1, GetWindowPos( ).y + 26 }, GetColorU32( ImGuiCol_Border, 0.4f ), GetColorU32( ImGuiCol_Border, 0.4f ), GetColorU32( ImGuiCol_Border, 0.05f ), GetColorU32( ImGuiCol_Border, 0.05f ) );
    GetWindowDrawList( )->AddRectFilledMultiColor( { GetWindowPos( ).x + 1, GetWindowPos( ).y + 26 }, { GetWindowPos( ).x + GetWindowWidth( ) / 2 - 20, GetWindowPos( ).y + 27 }, GetColorU32( ImGuiCol_Border ), GetColorU32( ImGuiCol_Border, 0.f ), GetColorU32( ImGuiCol_Border, 0.f ), GetColorU32( ImGuiCol_Border ) );
    GetWindowDrawList( )->AddRectFilledMultiColor( { GetWindowPos( ).x + GetWindowWidth( ) / 2 + 20, GetWindowPos( ).y + 26 }, { GetWindowPos( ).x + GetWindowWidth( ) - 1, GetWindowPos( ).y + 27 }, GetColorU32( ImGuiCol_Border, 0.f ), GetColorU32( ImGuiCol_Border ), GetColorU32( ImGuiCol_Border ), GetColorU32( ImGuiCol_Border, 0.f ) );
    add_text( font, 13, { GetWindowPos( ).x + 7, GetWindowPos( ).y + 26 / 2 - 13 / 2 - 1 }, GetColorU32( ImGuiCol_TextDisabled ), label, FindRenderedTextEnd( label ) );
    GetWindowDrawList( )->AddRect( GetWindowPos( ), GetWindowPos( ) + GetWindowSize( ), GetColorU32( ImGuiCol_Border ) );

    SetCursorPosY( 28 );
    PushStyleVar( ImGuiStyleVar_ItemSpacing, { 8, 8 } );
    PushStyleVar( ImGuiStyleVar_WindowPadding, { 13, 10 } );
    BeginChild( label, { -1, size.y == 0 ? size.y : -1 }, 0, ImGuiWindowFlags_AlwaysUseWindowPadding | ImGuiWindowFlags_NoBackground );
}

void ui::end_child( ) {
    PopStyleVar( 2 );
    EndChild( );
    EndChild( );
}













































































































































































































