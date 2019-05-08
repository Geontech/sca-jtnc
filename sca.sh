
if [ "X$SCAHOME" = X ] ; then
    export SCAHOME=/usr/local/sca/core
    if [ "X$PATH" != X ]; then
        PATH=:${PATH}
    fi
    export PATH=/usr/local/sca/core/bin${PATH}
    if [ "X$LD_LIBRARY_PATH" != X ]; then
        LD_LIBRARY_PATH=:${LD_LIBRARY_PATH}
    fi
    export LD_LIBRARY_PATH=/usr/local/sca/core/lib:/usr/local/sca/core/lib64${LD_LIBRARY_PATH}
    if [ "X$PKG_CONFIG_PATH" != X ]; then
        PKG_CONFIG_PATH=:${PKG_CONFIG_PATH}
    fi
    export PKG_CONFIG_PATH=/usr/local/sca/core/lib/pkgconfig:/usr/local/sca/core/lib64/pkgconfig${PKG_CONFIG_PATH}
    if [ "X$PYTHONPATH" != X ]; then
        PYTHONPATH=:${PYTHONPATH}
    fi
    export PYTHONPATH=${SCAHOME}/lib64/python:${SCAHOME}/lib/python${PYTHONPATH}
fi
if [ "X$LD_LIBRARY_PATH" = X ] ; then
    export LD_LIBRARY_PATH=/usr/local/sca/core/lib64
fi

