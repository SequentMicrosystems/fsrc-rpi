Welcome to SMfsrc's documentation!
===================================

Install
=======

.. code-block:: bash

    sudo pip install SMfsrc

or

.. code-block:: bash

    sudo pip3 install SMfsrc

Update
======

.. code-block:: bash

    sudo pip install SMfsrc -U

or

.. code-block:: bash

    sudo pip3 install SMfsrc -U

Local Installation
==================

.. code-block:: bash

    git clone https://github.com/SequentMicrosystems/fsrc-rpi.git
    cd ~/fsrc-rpi/python
    sudo python setup.py install

Initiate class
==============

.. code-block:: console

   $ python
   Python 3.9.2 (default, Feb 28 2021, 17:03:44) 
   [GCC 10.2.1 20210110] on linux
   Type "help", "copyright", "credits" or "license" for more information.
   >>> import SMfsrc
   >>> fsrc = SMfsrc.SMfsrc()
   >>> fsrc.get_digi(1)
   >>>


Documentation
=============

.. toctree::
   :maxdepth: 2
   :caption: Contents:

.. automodule:: SMfsrc
   :members:
   :undoc-members:
   :show-inheritance:

.. vi:se ts=4 sw=4 et:
