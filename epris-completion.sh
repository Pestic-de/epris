#
# bash completion support for Epris/Epr.
#
# Copyright (C) 2008, 2009 Marc-Andre Lureau <marcandre.lureau@gmail.com>
# Copyright (C) 2006,2007 Shawn O. Pearce <spearce@spearce.org>
#
# _completely_ based on git-completion.sh (from Git) :)
# Distributed under the GNU General Public License, version 2.0.
#

case "$COMP_WORDBREAKS" in
*:*) : great ;;
*)   COMP_WORDBREAKS="$COMP_WORDBREAKS:"
esac

__epr_has_doubledash ()
{
        local c=1
        while [ $c -lt $COMP_CWORD ]; do
                if [ "--" = "${COMP_WORDS[c]}" ]; then
                        return 0
                fi
                c=$((++c))
        done
        return 1
}

__eprcomp_1 ()
{
        local c IFS=' '$'\t'$'\n'
        for c in $1; do
                case "$c$2" in
                --*=*) printf %s$'\n' "$c$2" ;;
                *.)    printf %s$'\n' "$c$2" ;;
                *)     printf %s$'\n' "$c$2 " ;;
                esac
        done
}

__eprcomp ()
{
        local cur="${COMP_WORDS[COMP_CWORD]}"
        if [ $# -gt 2 ]; then
                cur="$3"
        fi
        case "$cur" in
        --*=)
                COMPREPLY=()
                ;;
        *)
                local IFS=$'\n'
                COMPREPLY=($(compgen -P "$2" \
                        -W "$(__eprcomp_1 "$1" "$4")" \
                        -- "$cur"))
                ;;
        esac
}

__epr_all_commands ()
{
        local i IFS=" "$'\n'
        for i in $(epr help -a | cut -d"
" -f 6- | grep '^  [^-]' | cut -d' ' -f 3)
        do
                case $i in
                *--*)             : helper pattern;;
                *) echo $i;;
                esac
        done
}
__epr_all_commandlist=
__epr_all_commandlist="$(__epr_all_commands 2>/dev/null)"

__epr_porcelain_commands ()
{
        local i IFS=" "$'\n'
        for i in "help" $(__epr_all_commands)
        do
                case $i in
                *--*)             : helper pattern;;
                seek)             : plumbing;;
                *) echo $i;;
                esac
        done
}

_epr ()
{
    local i c=1 command

    while [ $c -lt $COMP_CWORD ]; do
        i="${COMP_WORDS[c]}"
        case "$i" in
            --version) ;;
            --help) command="help"; break ;;
            *) command="$i"; break ;;
        esac
        c=$((++c))
    done

    if [ -z "$command" ]; then
        case "${COMP_WORDS[COMP_CWORD]}" in
            --*=*) COMPREPLY=() ;;
            --*)   __eprcomp "
                        --debug-level
                        --version
                        --help
                        "
                        ;;
	    *)     __eprcomp "$(__epr_porcelain_commands)" ;;
        esac
        return
    fi

    case "$command" in
        *)           COMPREPLY=() ;;
    esac

}

_epris ()
{
        __epr_has_doubledash && return

        local cur="${COMP_WORDS[COMP_CWORD]}"
        case "$cur" in
        --*)
                __eprcomp "--debug-level --gst-debug-level --version --help"
                return
                ;;
        esac
}

complete -o default -o nospace -F _epr epr
complete -o default -o nospace -F _epris epris
